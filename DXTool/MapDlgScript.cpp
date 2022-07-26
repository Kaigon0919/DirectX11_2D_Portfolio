#include "stdafx.h"
#include "MapDlgScript.h"
#include<Camera.h>
#include<DxDebug.h>
#include<InputManager.h>
#include<TileMapRender.h>
#include<Tex.h>
#include<GameSprite.h>
#include<BWStream.h>
#include<BRStream.h>
#include<Render2DSprite.h>
#include<Col2DRect.h>
#include"MapDlg.h"
bool MapDlgScript::Init()
{
	GetLevel()->RMgr.YSortOn(1);

	const wchar_t * tileImage = L"Tile.png";
	int row = 1,col = 2;

	m_CameraActor = GetLevel()->CreateActor(L"Camera");
	SPTR<Camera> Ptr = m_CameraActor->AddComponent<Camera>();
	Ptr->OnViewGroup(0, 1, 2, 3);
	m_CameraActor->GetTransform()->SetWorldPosition(Vector3f(0.0f, 0.0f, -100.0f));


	if (ResMgr<Tex>::Find(tileImage) == nullptr)
		ResMgr<Tex>::Load(PathManager::FindPath(L"Tex") + tileImage);
	if (ResMgr<GameSprite>::Find(tileImage) == nullptr)
		ResMgr<GameSprite>::Create(tileImage, tileImage, col, row);


	SPTR<Actor> MapActor = GetLevel()->CreateActor(L"Tile");
	MapActor->GetTransform()->Translate(0.0, 0.0f, 0.0f);

	m_SpriteRender = MapActor->AddComponent<Render2DSprite>(0);
	m_SpriteRender->SetWorldSubPosition(Vector3f(0.0f, 0.0f, 100.0f));
	m_SpriteRender->SetCutShow(false);

	m_MapRender = MapActor->AddComponent<TileMapRender>(3);
	m_MapRender->SetSprite(tileImage);
	m_MapRender->SetTileSize(ResMgr<GameSprite>::Find(tileImage)->GetSpriteImageSize(0));

	return true;
}

bool MapDlgScript::Loading()
{
	return false;
}

void MapDlgScript::Update()
{
	float heel = InputManager::GetMouseWHeel() / 120.0f * 0.01f;
	if (heel != 0)
	{
		GetLevel()->GetMainCamera()->AddZoom(heel);
	}

	switch (m_Mode)
	{
	case 0:
		if (true == InputManager::IsPressed(L"LButton"))
		{
			m_MapRender->CreateTile(GetLevel()->GetMainCamera()->ScreenToClient(InputManager::GetMousePos()), SelectTile);
		}
		if (true == InputManager::IsPressed(L"RButton"))
		{
			m_MapRender->DeleteTile(GetLevel()->GetMainCamera()->ScreenToClient(InputManager::GetMousePos()));
		}
		if (InputManager::IsDown(L"C"))
		{
			m_MapRender->Clear();
		}
		break;
	case 1:
		break;
	case 2:
		if (true == InputManager::IsDown(L"LButton"))
		{
			CreateObject(GetLevel()->GetMainCamera()->ScreenToClient(InputManager::GetMousePos()), ObjectSpriteName.c_str());
			MapDlg::NewUpdate();
		}
		if (InputManager::IsPressed(L"C"))
		{
			ObjectClear();
			MapDlg::NewUpdate();
		}
		break;
	}
	if (InputManager::IsPressed(L"LEFT") || InputManager::IsPressed(L"A"))
	{
		m_CameraActor->GetTransform()->Translate(-1.0f, 0.0f, 0.0f);
	}
	if (InputManager::IsPressed(L"RIGHT") || InputManager::IsPressed(L"D"))
	{
		m_CameraActor->GetTransform()->Translate(1.0f, 0.0f, 0.0f);
	}
	if (InputManager::IsPressed(L"UP") || InputManager::IsPressed(L"W"))
	{
		m_CameraActor->GetTransform()->Translate(0.0f, 1.0f, 0.0f);
	}
	if (InputManager::IsPressed(L"DOWN") || InputManager::IsPressed(L"S"))
	{
		m_CameraActor->GetTransform()->Translate(0.0f, -1.0f, 0.0f);
	}
	if(isCheck)
		SpriteCheck();
}

void MapDlgScript::DebugRender()
{
	wchar_t DebugOutText[1024];

	Vector2i mousePos = GetLevel()->GetMainCamera()->ScreenToClient(InputManager::GetMousePos());
	swprintf_s(DebugOutText, L"Player WorldPosotion : ( x : %d , y : %d )", mousePos.x, mousePos.y);
	DxDebug::DrawStr(DebugOutText, 30, Vector2i(10, 10), Color4f(0.0f, 0.0f, 0.0f));

}

size_t MapDlgScript::GetTileCutSize() const
{
	return m_MapRender->GetTileSetSize();
}

void MapDlgScript::MapSave()
{
	std::wstring DlgPath = PathManager::FindPath(L"MapData");
	if (DlgPath == L"")
	{
		assert(false && L"Not FindPath MapData");
		return;
	}

	std::wstring defSave = m_SpriteName;
	if(defSave == L"")
	{
		defSave = L"default.data";
	}
	else
	{
		size_t CutCount = defSave.find_last_of(L'.', defSave.size());
		defSave = defSave.replace(CutCount, defSave.size(), L".data");
	}
	CFileDialog dlgFile(FALSE);
	OPENFILENAME& ofn = dlgFile.GetOFN();
	ofn.lpstrInitialDir = DlgPath.c_str();
	ofn.lpstrDefExt = L"data";
	ofn.lpstrFilter = L"Data File\0 *.data\0Every File\0*.*\0";

	lstrcpyW(ofn.lpstrFile, defSave.c_str());

	if (dlgFile.DoModal() == IDCANCEL)
	{
		return;
	}

	// 파일명.
	//CString FileName = dlgFile.GetFileName();
	// 파일명까지의 경로.
	CString PathName = dlgFile.GetPathName();
	// 폴더경로 (파일명 X)
	//CString FolderPath = dlgFile.GetFolderPath();
	if (PathName == L"")
	{
		return;
	}

	BWFStream bis = BWFStream(PathName);
	// Sprite Name Save.
	wchar_t saveSprite[1024];
	lstrcpyW(saveSprite, m_SpriteName.c_str());
	bis.Write(saveSprite);

	// Gate Data Save.
	int GateSize = (int)m_GateList.size();
	bis.Write(GateSize);

	std::unordered_map<Actor*, GateData>::iterator itStart = m_GateMap.begin();
	std::unordered_map<Actor*, GateData>::iterator itEnd = m_GateMap.end();
	for (; itStart != itEnd; ++itStart)
	{
		bis.Write(itStart->second);
	}

	// Object Data Save.
	int ObjectSize = (int)m_ObjectList.size();
	bis.Write(ObjectSize);
	std::unordered_map<Actor*, ObjectData>::iterator itObjStart = m_ObjectMap.begin();
	std::unordered_map<Actor*, ObjectData>::iterator itObjEnd = m_ObjectMap.end();
	for (; itObjStart != itObjEnd; ++itObjStart)
	{
		bis.Write(itObjStart->second);
	}

	// Tail Data Save.
	std::list<TileMapRender::IOTileData> List = m_MapRender->IOAllData();
	
	int size = (int)List.size();
	bis.Write(size);
	std::list<TileMapRender::IOTileData>::iterator StartIter = List.begin();
	std::list<TileMapRender::IOTileData>::iterator EndIter = List.end();

	for (; StartIter != EndIter; ++StartIter)
	{
		bis.Write((*StartIter));
	}
}

void MapDlgScript::MapLoad()
{
	std::wstring DlgPath = PathManager::FindPath(L"MapData");
	if (DlgPath == L"")
	{
		DlgPath = PathManager::GetRootPath();
	}
	CFileDialog dlgFile(true);
	OPENFILENAME& ofn = dlgFile.GetOFN();
	ofn.lpstrInitialDir = DlgPath.c_str();
	ofn.lpstrDefExt = L"data";
	ofn.lpstrFilter = L"Data File\0 *.data\0Every File\0*.*\0";
	if (dlgFile.DoModal() == IDCANCEL)
	{
		return;
	}
	CString PathName = dlgFile.GetPathName();
	if (PathName == L"")
	{
		return;
	}

	m_MapRender->Clear();
	std::list<SPTR<Actor>>::iterator itStart = m_GateList.begin();
	std::list<SPTR<Actor>>::iterator itEnd = m_GateList.end();
	for (; itStart != itEnd;++itStart)
	{
		(*itStart)->Death();
	}
	m_GateList.clear();
	m_GateMap.clear();

	ObjectClear();

	BRStream Stream = BRStream(PathName);

	// Sprite Load.
	wchar_t spriteName[1024];
	Stream.Read(spriteName);

	SpriteSetting(spriteName);
	m_SpriteName = spriteName;

	// Gate Load.
	int GateSize;
	Stream.Read(GateSize);

	GateData gateData;
	for (int i = 0; i < GateSize; ++i)
	{
		Stream.Read(gateData);
		CreateGate(gateData.Mode, gateData.Pos, gateData.Scale, gateData.NextLevel, gateData.NextPos);
	}
	// Object Load.
	int ObjectSize;
	Stream.Read(ObjectSize);

	ObjectData objectData;
	for (int i = 0; i < ObjectSize; ++i)
	{
		Stream.Read(objectData);
		CreateObject(objectData.Pos, objectData.SpriteName);
	}

	// Tile Load.
	int size;
	Stream.Read(size);

	TileMapRender::IOTileData data;

	for (int i = 0; i < size; ++i)
	{
		Stream.Read(data);
		m_MapRender->CreateTile(data.index, data.SpriteIndex);
	}

}


void MapDlgScript::SpriteCheck()
{
	if (ResMgr<Tex>::Find(inputSpriteName) == nullptr)
	{
		return;
	}
	SpriteSetting(inputSpriteName.c_str());
	m_SpriteName = inputSpriteName;

	isCheck = false;
}

void MapDlgScript::SpriteSetting(const wchar_t * sprite)
{
	if (ResMgr<GameSprite>::Find(sprite) == nullptr)
	{
		if (ResMgr<Tex>::Find(sprite) == nullptr)
		{
			return;
		}
		ResMgr<GameSprite>::Create(sprite, sprite);
	}
	m_SpriteRender->SetSprite(sprite);
	m_SpriteRender->SetLocalSubScale(m_SpriteRender->GetSpriteImageSize(0));
	m_SpriteRender->SetLocalSubPosition(Vector3f(0.0f, 0.0f, 10.0f));
}

size_t MapDlgScript::GetGateSize() const
{
	return m_GateList.size();
}

void MapDlgScript::CreateGate(int Mode, Vector2f Pos, Vector2f Scale, const wchar_t * NextLevel, Vector2f NextPos)
{
	GateData data;
	data.Mode = Mode;
	data.Pos = Pos;
	data.Scale = Scale;
	lstrcpyW(data.NextLevel, NextLevel);
	data.NextPos = NextPos;

	SPTR<Actor> actor = GetLevel()->CreateActor(0);
	actor->GetTransform()->SetWorldPosition(Pos.x, Pos.y, 0.0f);
	SPTR<Col2DRect> Col = actor->AddComponent<Col2DRect>();
	Col->SetLocalSubScale(Vector3f(Scale.x, Scale.y, 1.0f));

	m_GateList.push_back(actor);
	m_GateMap.insert(std::unordered_map<Actor*, GateData>::value_type(actor.Get(), data));
}

void MapDlgScript::DeleteGate(int index)
{
	if (index < 0 || index >= m_GateList.size())
	{
		return;
	}
	std::list<SPTR<Actor>>::iterator itStart = m_GateList.begin();

	for (int i = 0; i < index; ++i)
	{
		++itStart;
	}

	std::unordered_map<Actor*, GateData>::iterator find = m_GateMap.find((*itStart).Get());
	if (find == m_GateMap.end())
	{
		assert(false);
	}
	(*itStart)->Death();
	m_GateMap.erase(find);
	m_GateList.erase(itStart);
}

GateData MapDlgScript::GetGateData(int index)
{
	if (index < 0 || index >= m_GateList.size())
	{
		return GateData();
	}
	std::list<SPTR<Actor>>::iterator itStart = m_GateList.begin();

	for (int i = 0; i < index; ++i)
	{
		++itStart;
	}

	std::unordered_map<Actor*, GateData>::iterator find = m_GateMap.find((*itStart).Get());
	if (find == m_GateMap.end())
	{
		assert(false);
		return GateData();
	}
	return find->second;
}

void MapDlgScript::CreateObject(Vector2f Pos,const wchar_t * SpirteName)
{
	if (lstrcmp(SpirteName, L"") == 0)
	{
		return;
	}
	if (ResMgr<GameSprite>::Find(SpirteName) == nullptr)
	{
		ResMgr<GameSprite>::Create(SpirteName, SpirteName);
	}
	ObjectData data;
	data.Pos = Pos;
	lstrcpyW(data.SpriteName, SpirteName);

	SPTR<Actor> actor = GetLevel()->CreateActor(0);
	actor->GetTransform()->SetWorldPosition(Pos.x, Pos.y, 0.0f);
	SPTR<Render2DSprite> render = actor->AddComponent<Render2DSprite>();
	render->SetSprite(SpirteName);

	Vector3f RenderSize = render->GetSpriteImageSize(0);
	render->SetLocalSubScale(RenderSize);
	Vector3f RenderPos;
	RenderPos.x = 0.0f;
	RenderPos.y = RenderSize.y / 2.0f;
	render->SetLocalSubPosition(RenderPos);

	m_ObjectList.push_back(actor);
	m_ObjectMap.insert(std::unordered_map<Actor*, ObjectData>::value_type(actor.Get(), data));
}

void MapDlgScript::DeleteObject(int index)
{
	if (index < 0 || index >= m_ObjectList.size())
	{
		return;
	}
	std::list<SPTR<Actor>>::iterator itStart = m_ObjectList.begin();

	for (int i = 0; i < index; ++i)
	{
		++itStart;
	}

	std::unordered_map<Actor*, ObjectData>::iterator find = m_ObjectMap.find((*itStart).Get());
	if (find == m_ObjectMap.end())
	{
		assert(false);
	}
	(*itStart)->Death();
	m_ObjectMap.erase(find);
	m_ObjectList.erase(itStart);
}

void MapDlgScript::ObjectClear()
{
	std::list<SPTR<Actor>>::iterator itStart = m_ObjectList.begin();
	std::list<SPTR<Actor>>::iterator itEnd = m_ObjectList.end();
	for (; itStart != itEnd; ++itStart)
	{
		(*itStart)->Death();
	}
	m_ObjectList.clear();
	m_ObjectMap.clear();
}

size_t MapDlgScript::GetObjSIze() const
{
	return m_ObjectList.size();
}

ObjectData MapDlgScript::GetObjData(int index)
{
	if (index < 0 || index >= m_ObjectList.size())
	{
		return ObjectData();
	}
	std::list<SPTR<Actor>>::iterator itStart = m_ObjectList.begin();

	for (int i = 0; i < index; ++i)
	{
		++itStart;
	}

	std::unordered_map<Actor*, ObjectData>::iterator find = m_ObjectMap.find((*itStart).Get());
	if (find == m_ObjectMap.end())
	{
		assert(false);
		return ObjectData();
	}
	return find->second;
}

MapDlgScript::MapDlgScript() : SelectTile(0), m_MapRender(nullptr), isCheck(false)
{
}


MapDlgScript::~MapDlgScript()
{
}
