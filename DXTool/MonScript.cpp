#include "stdafx.h"
#include "MonScript.h"
#include<Camera.h>
#include<RenderParts.h>
#include<BWStream.h>
#include<BRStream.h>
#include<Render2DSprite.h>
#include<TileMapRender.h>
#include<GameSprite.h>
#include<Col2DRect.h>
#include<Tex.h>


bool MonScript::Init()
{
	GetLevel()->RMgr.YSortOn(1);

	m_CameraActor = GetLevel()->CreateActor(L"Camera");
	SPTR<Camera> Ptr = m_CameraActor->AddComponent<Camera>();
	Ptr->OnViewGroup(0, 1, 2, 3);
	m_CameraActor->GetTransform()->SetWorldPosition(Vector3f(0.0f, 0.0f, -100.0f));

	SPTR<Actor> actor = GetLevel()->CreateActor(L"Back");
	m_BackGround = actor->AddComponent<Render2DSprite>(0);
	m_TileMap = actor->AddComponent<TileMapRender>(0);


	const wchar_t * tileImage = L"Tile.png";
	int row = 1, col = 2;
	if (ResMgr<Tex>::Find(tileImage) == nullptr)
		ResMgr<Tex>::Load(PathManager::FindPath(L"Tex") + tileImage);
	if (ResMgr<GameSprite>::Find(tileImage) == nullptr)
		ResMgr<GameSprite>::Create(tileImage, tileImage, col, row);
	m_TileMap->SetSprite(tileImage);

	return true;
}

bool MonScript::Loading()
{


	return true;
}

void MonScript::Update()
{
	if (true == InputManager::IsDown(L"LButton"))
	{
		CreateMon(m_Type, GetLevel()->GetMainCamera()->ScreenToClient(InputManager::GetMousePos()));
	}
	if (InputManager::IsDown(L"C"))
	{
		Clear();
	}
}

void MonScript::DebugRender()
{
}

void MonScript::Save()
{
	std::wstring DlgPath = PathManager::FindPath(L"MonsterBat");
	if (DlgPath == L"")
	{
		assert(false && L"Not FindPath MonsterBat");
		return;
	}

	std::wstring defSave = m_SpriteName;
	if (defSave == L"")
	{
		defSave = L"default_mon.data";
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
	int MonSize = (int)m_MonList.size();
	bis.Write(MonSize);

	std::unordered_map<Actor*, MonData>::iterator itStart = m_MonMap.begin();
	std::unordered_map<Actor*, MonData>::iterator itEnd = m_MonMap.end();
	for (; itStart != itEnd; ++itStart)
	{
		bis.Write(itStart->second);
	}

}

void MonScript::Load()
{
	std::wstring DlgPath = PathManager::FindPath(L"MonsterBat");
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
	Clear();
	BRStream Stream = BRStream(PathName);

	int size;
	Stream.Read(size);
	MonData data;
	for (int i = 0; i < size; ++i)
	{
		Stream.Read(data);
		CreateMon(data.MonType, data.Pos);
	}
}

void MonScript::Clear()
{
	std::list<SPTR<Actor>>::iterator itStart = m_MonList.begin();
	std::list<SPTR<Actor>>::iterator itEnd = m_MonList.end();
	for (; itStart != itEnd; ++itStart)
	{
		(*itStart)->Death();
	}
	m_MonList.clear();
	m_MonMap.clear();
}

void MonScript::SpriteLoad()
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

	m_TileMap->Clear();
	std::list<SPTR<Actor>>::iterator itStart = m_GateList.begin();
	std::list<SPTR<Actor>>::iterator itEnd = m_GateList.end();
	for (; itStart != itEnd; ++itStart)
	{
		(*itStart)->Death();
	}
	m_GateList.clear();

	itStart = m_ObjList.begin();
	itEnd = m_ObjList.end();
	for (; itStart != itEnd; ++itStart)
	{
		(*itStart)->Death();
	}
	m_ObjList.clear();

	BRStream Stream = BRStream(PathName);

	// Sprite Load.
	wchar_t spriteName[1024];
	Stream.Read(spriteName);

	if (ResMgr<GameSprite>::Find(spriteName) == nullptr)
	{
		if (ResMgr<Tex>::Find(spriteName) == nullptr)
		{
			return;
		}
		ResMgr<GameSprite>::Create(spriteName, spriteName);
	}
	m_BackGround->SetSprite(spriteName);
	m_BackGround->SetLocalSubScale(m_BackGround->GetSpriteImageSize(0));
	m_BackGround->SetLocalSubPosition(Vector3f(0.0f, 0.0f, 10.0f));
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
		m_TileMap->CreateTile(data.index, data.SpriteIndex);
	}
}

void MonScript::CreateMon(int type, Vector2f Pos)
{
	SPTR<Actor> actor = GetLevel()->CreateActor();
	actor->GetTransform()->SetWorldPosition(Vector3f(Pos.x, Pos.y, 0.0f));
	SPTR<RenderParts> Part = actor->AddComponent<RenderParts>();
	switch (type)
	{
	case 0:
		if (ResMgr<GameSprite>::Find(L"GoblinBody0.png") == nullptr)
		{
			ResMgr<GameSprite>::Create(L"GoblinBody0.png", L"GoblinBody0.png", 6, 3);
		}
		Part->SettingPart(RenderParts::RP_Skin, L"GoblinBody0.png", L"GoblinBody0.data");
		Part->SetPivot(Vector2i(0, 55));

		break;
	case 1:
		if (ResMgr<GameSprite>::Find(L"GoblinBody1.png") == nullptr)
		{
			ResMgr<GameSprite>::Create(L"GoblinBody1.png", L"GoblinBody1.png", 6, 3);
			ResMgr<GameSprite>::Create(L"GoblinWeapon1.png", L"GoblinWeapon1.png", 6, 3);
		}
		Part->SettingPart(RenderParts::RP_Skin, L"GoblinBody1.png", L"GoblinBody1.data");
		Part->SettingPart(RenderParts::RP_WeaponA, L"GoblinWeapon1.png", L"GoblinWeapon1.data");
		Part->SetPivot(Vector2i(0, 55));
		break;
	case 2:
		if (ResMgr<GameSprite>::Find(L"Tau.png") == nullptr)
		{
			ResMgr<GameSprite>::Create(L"Tau.png", L"Tau.png", 8, 4);
		}
		Part->SettingPart(RenderParts::RP_Skin, L"Tau.png", L"Tau.data");
		Part->SetPivot(Vector2i(20, 80));
		break;
	}
	MonData data;
	data.MonType = type;
	data.Pos = Pos;

	m_MonList.push_back(actor);
	m_MonMap.insert(std::unordered_map<Actor*, MonData>::value_type(actor.Get(), data));

}

void MonScript::CreateGate(int Mode, Vector2f Pos, Vector2f Scale, const wchar_t * NextLevel, Vector2f NextPos)
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
}

void MonScript::CreateObject(Vector2f Pos, const wchar_t * SpirteName)
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
	render->SetLocalSubScale(render->GetSpriteImageSize(0));

	Vector3f RenderSize = render->GetSpriteImageSize(0);
	render->SetLocalSubScale(RenderSize);
	Vector3f RenderPos;
	RenderPos.x = 0.0f;
	RenderPos.y = RenderSize.y / 2.0f;
	render->SetLocalSubPosition(RenderPos);


	m_ObjList.push_back(actor);
}

MonScript::MonScript() : m_Type(0)
{

}


MonScript::~MonScript()
{
}
