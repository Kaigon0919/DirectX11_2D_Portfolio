#include "BackGround.h"
#include<Render2DSprite.h>
#include<TileMapRender.h>
#include<BRStream.h>

#include<Tex.h>
#include<GameSprite.h>
#include<SaveAndLoadData.h>
#include<Level.h>
#include"Gate.h"
bool BackGround::Init()
{
	SPTR<Transform> trans = GetComponent<Transform>();
	trans->SetLocalPosition(0.0f, 0.0f, 100.0f);
	trans->SetLocalScale(1.0f, 1.0f, 1.0f);
	
	
	m_TileMap = AddComponent<TileMapRender>(1);
	m_TileMap->SetLocalSubPosition(Vector3f(0.0f, 0.0f, -0.1f));

	const wchar_t * tileImage = L"Tile.png";
	int row = 1, col = 2;

	if (ResMgr<Tex>::Find(tileImage) == nullptr)
		ResMgr<Tex>::Load(PathManager::FindPath(L"Tex") + tileImage);
	if (ResMgr<GameSprite>::Find(tileImage) == nullptr)
		ResMgr<GameSprite>::Create(tileImage, tileImage, col, row);

#ifdef _DEBUG
	m_TileMap->SetUpdate(true);
#else
	m_TileMap->SetUpdate(false);
#endif

	m_TileMap->SetSprite(tileImage);
	return true;
}

void BackGround::Update()
{

}

void BackGround::DataLoad(const wchar_t * FileName)
{
	std::wstring Path = PathManager::FindPath(L"MapData") + FileName;
	BRStream Stream = BRStream(Path.c_str());

	// Sprite Load.
	wchar_t spriteName[1024];
	Stream.Read(spriteName);

	m_Render = AddComponent<Render2DSprite>(0);
	m_Render->SetSprite(spriteName);

	SPTR<Transform> trans = GetComponent<Transform>();
	trans->SetLocalScale(m_Render->GetImageSIze());

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

void BackGround::CreateGate(int Mode, Vector2f Pos, Vector2f Scale, const wchar_t * NextLevel, Vector2f NextPos)
{
	SPTR<Actor> Warp = GetActor()->GetLevel()->CreateActor(L"Warp");
	SPTR<Gate> ComWarp = Warp->AddComponent<Gate>();
	Warp->GetTransform()->SetLocalPosition(Vector3f(Pos.x, Pos.y, 0.0f));
	Warp->GetTransform()->SetLocalScale(Vector3f(Scale.x, Scale.y, 0.0f));
	ComWarp->SetNextLevel(NextLevel);
	ComWarp->SetNextPos(Vector3f(NextPos.x, NextPos.y, 0.0f));
	ComWarp->SetType((Gate::GateType)Mode);
	m_Warps.push_back(Warp);
}

void BackGround::CreateObject(Vector2f Pos, const wchar_t * SpriteName)
{
	SPTR<Actor> Obj = GetActor()->GetLevel()->CreateActor(L"Object");
	SPTR<Render2DSprite> render = Obj->AddComponent<Render2DSprite>(1);
	render->SetSprite(SpriteName);
	
	Vector3f RenderSize = render->GetSpriteImageSize(0);
	
	Obj->GetTransform()->SetLocalPosition(Vector3f(Pos.x, Pos.y, 0.0f));
	
	render->SetLocalSubScale(RenderSize);
	Vector3f RenderPos;
	RenderPos.x = 0.0f;
	RenderPos.y = RenderSize.y / 2.0f;
	render->SetLocalSubPosition(RenderPos);

	m_Objs.push_back(Obj);
}

void BackGround::CloseGate()
{
	std::list<SPTR<Actor>>::iterator itStart =  m_Warps.begin();
	std::list<SPTR<Actor>>::iterator itEnd = m_Warps.end();
	for (; itStart != itEnd; ++itStart)
	{
		(*itStart)->SetUpdate(false);
	}
}

void BackGround::OpenGate()
{
	std::list<SPTR<Actor>>::iterator itStart = m_Warps.begin();
	std::list<SPTR<Actor>>::iterator itEnd = m_Warps.end();
	for (; itStart != itEnd; ++itStart)
	{
		(*itStart)->SetUpdate(true);
	}
}

void BackGround::SetFade(SPTR<Fade> fade)
{
	std::list<SPTR<Actor>>::iterator itStart = m_Warps.begin();
	std::list<SPTR<Actor>>::iterator itEnd = m_Warps.end();
	for (; itStart != itEnd; ++itStart)
	{
		SPTR<Gate> taget = (*itStart)->GetComponent<Gate>();
		taget->SetFaid(fade);
	}
}

BackGround::BackGround()
{
}


BackGround::~BackGround()
{
}
