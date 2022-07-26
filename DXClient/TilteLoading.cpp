#include "TilteLoading.h"
#include<MyThread.h>
#include<Tex.h>
#include<GameSprite.h>
#include<Camera.h>
#include<Render2DSprite.h>
#include<MainWindow.h>
#include<TimeManager.h>
#include<DxDebug.h>
#include<InputManager.h>
#include<Level.h>
#include<Actor.h>
#include<MySound.h>
#include<MySoundPlayer.h>
bool TilteLoading::Loading()
{
	ResMgr<Tex>::Load(PathManager::FindPath(L"Tex") + L"Loading\\Loading0.png");
	ResMgr<Tex>::Load(PathManager::FindPath(L"Tex") + L"Loading\\Loading4.png");
	ResMgr<Tex>::Load(PathManager::FindPath(L"Tex") + L"Loading\\Loading7.png");

	ResMgr<GameSprite>::Create(L"Loading0.png", L"Loading0.png");
	ResMgr<GameSprite>::Create(L"Loading4.png", L"Loading4.png");
	ResMgr<GameSprite>::Create(L"Loading7.png", L"Loading7.png");

	GetLevel()->RMgr.ZSortOn(1);

	m_Camera = GetLevel()->CreateActor(L"Camera");
	SPTR<Camera> comCamera = m_Camera->AddComponent<Camera>();
	m_Camera->GetTransform()->SetLocalPosition(0.0f, 0.0f, -100.0f);
	comCamera->OnViewGroup(0, 1);
	comCamera->SetZoom(1.0f);

	m_Back = GetLevel()->CreateActor(L"Background");
	SPTR<Render2DSprite> Render1 = m_Back->AddComponent<Render2DSprite>();
	Render1->SetSprite(L"Loading0.png");
	Render1->SetLocalSubScale(MainWindow::GetSize());

	
	loading = GetLevel()->CreateActor(L"Background");
	SPTR<Render2DSprite> Render2 = loading->AddComponent<Render2DSprite>();
	Render2->SetSprite(L"Loading7.png");
	Render2->SetLocalSubPosition(Vector3f(560, -255.0f, -0.1f));
	Render2->SetLocalSubScale(Render2->GetSpriteImageSize(0));

	rot = loading->AddComponent<Render2DSprite>();
	rot->SetSprite(L"Loading4.png");
	rot->SetLocalSubPosition(Vector3f(565, -276.0f, -0.2f));
	rot->SetLocalSubScale(rot->GetSpriteImageSize(0));
	rot->SetTransColor(Color4f(0.0f, 0.0f, 0.0f, 1.0f));

	ResMgr<MySound>::Load(PathManager::FindPath(L"Sound") + L"character_stage.ogg");
	m_Sound = m_Back->AddComponent<MySoundPlayer>();
	m_Sound->Play(L"character_stage.ogg", true);


	MyThread::CreateMemberThread<TilteLoading>(L"LoadThread", &TilteLoading::DataLoad, this);

	return true;
}

void TilteLoading::Start()
{
}

void TilteLoading::Update()
{
	rot->SetLocalSubRotate(rot->GetLocalSubRotate() + Vector3f(0.0f, 0.0f, -360.0f) * TimeManager::GetDeltaTime());
	if (!isLoading)
	{
		GetLevel()->ChangeLevel(L"SeriaRoom");
	}
}

void TilteLoading::LateUpdate()
{
}

void TilteLoading::End()
{
	m_Sound->Stop();
}

void TilteLoading::DebugRender()
{
	wchar_t DebugOutText[1024];
	if (GetLevel()->GetMainCamera() != nullptr)
	{
		Vector2i mousePos = GetLevel()->GetMainCamera()->ScreenToClient(InputManager::GetMousePos());
		swprintf_s(DebugOutText, L"MousePos: ( x : %d , y : %d)", mousePos.x, mousePos.y);
		DxDebug::DrawStr(DebugOutText, 16, Vector2i(10, 50), Color4f(0.0f, 1.0f, 0.0f));
	}
}

unsigned int TilteLoading::DataLoad(void *)
{
	ResMgr<Tex>::TexLoadFileInDir(L"Tex");

	// Map.
	ResMgr<GameSprite>::Create(L"SeriaRoom.png", L"SeriaRoom.png");
	ResMgr<GameSprite>::Create(L"TempMap.png", L"TempMap.png");
	ResMgr<GameSprite>::Create(L"Village.png", L"Village.png");

	// Object.
	ResMgr<GameSprite>::SpriteCreate(L"Objects");
	/*ResMgr<GameSprite>::Create(L"seria_tree.png", L"seria_tree.png");
	ResMgr<GameSprite>::Create(L"sign_dungeon.png", L"sign_dungeon.png");
	ResMgr<GameSprite>::Create(L"leftgate.png", L"leftgate.png");
	ResMgr<GameSprite>::Create(L"leftgateboss.png", L"leftgateboss.png");
	ResMgr<GameSprite>::Create(L"rightgate.png", L"rightgate.png");
	ResMgr<GameSprite>::Create(L"rightgateboss.png", L"rightgateboss.png");*/

	// Character.
	ResMgr<GameSprite>::Create(L"Character_Swordman.png", L"Character_Swordman.png", 30, 7);
	ResMgr<GameSprite>::Create(L"sm_coat0000a.png", L"sm_coat0000a.png", 30, 7);
	ResMgr<GameSprite>::Create(L"sm_coat0200a_p1.png", L"sm_coat0200a_p1.png", 30, 7);
	ResMgr<GameSprite>::Create(L"sm_coat0200a_p2.png", L"sm_coat0200a_p2.png", 30, 7);
	ResMgr<GameSprite>::Create(L"sm_hair0000a.png", L"sm_hair0000a.png", 30, 7);
	ResMgr<GameSprite>::Create(L"sm_hair10000a.png", L"sm_hair10000a.png", 30, 7);
	ResMgr<GameSprite>::Create(L"sm_hair11200a.png", L"sm_hair11200a.png", 30, 7);
	ResMgr<GameSprite>::Create(L"sm_hair11500a.png", L"sm_hair11500a.png", 30, 7);
	ResMgr<GameSprite>::Create(L"lswd0000b.png", L"lswd0000b.png", 30, 7);
	ResMgr<GameSprite>::Create(L"lswd0000c.png", L"lswd0000c.png", 30, 7);
	ResMgr<GameSprite>::Create(L"sm_pants0000a.png", L"sm_pants0000a.png", 30, 7);
	ResMgr<GameSprite>::Create(L"sm_pants0000b.png", L"sm_pants0000b.png", 30, 7);

	ResMgr<GameSprite>::Create(L"sm_pants0200a.png", L"sm_pants0200a.png", 30, 7);
	ResMgr<GameSprite>::Create(L"sm_pants0200b.png", L"sm_pants0200b.png", 30, 7);

	ResMgr<GameSprite>::Create(L"sm_pants0201a.png", L"sm_pants0201a.png", 30, 7);
	ResMgr<GameSprite>::Create(L"sm_pants0201b.png", L"sm_pants0201b.png", 30, 7);

	ResMgr<GameSprite>::Create(L"sm_pants0202a.png", L"sm_pants0202a.png", 30, 7);
	ResMgr<GameSprite>::Create(L"sm_pants0202b.png", L"sm_pants0202b.png", 30, 7);
	ResMgr<GameSprite>::Create(L"sm_shoes0000a.png", L"sm_shoes0000a.png", 30, 7);
	ResMgr<GameSprite>::Create(L"sm_shoes0000b.png", L"sm_shoes0000b.png", 30, 7);
	
	// Effects.
	ResMgr<GameSprite>::Create(L"hardattackblade1.png", L"hardattackblade1.png", 1, 6);
	ResMgr<GameSprite>::Create(L"hardattackblade2.png", L"hardattackblade2.png", 1, 6);
	ResMgr<GameSprite>::Create(L"upperslash.png", L"upperslash.png", 1, 9);

	// Monster.
	ResMgr<GameSprite>::Create(L"GoblinBody0.png", L"GoblinBody0.png", 6, 3);
	ResMgr<GameSprite>::Create(L"GoblinBody1.png", L"GoblinBody1.png", 6, 3);
	ResMgr<GameSprite>::Create(L"GoblinWeapon1.png", L"GoblinWeapon1.png", 6, 3);
	ResMgr<GameSprite>::Create(L"GoblinWeapon2.png", L"GoblinWeapon2.png", 4, 1);
	ResMgr<GameSprite>::Create(L"Tau.png", L"Tau.png", 8, 4);

	// Hud & UI
	ResMgr<GameSprite>::Create(L"DamageFont.png", L"DamageFont.png", 10, 7);

	ResMgr<GameSprite>::SpriteCreate(L"Moninfo");

	//ResMgr<GameSprite>::Create(L"Moninfo0.png", L"Moninfo0.png");
	//ResMgr<GameSprite>::Create(L"Moninfo1.png", L"Moninfo1.png");
	//ResMgr<GameSprite>::Create(L"Moninfo2.png", L"Moninfo2.png");
	//ResMgr<GameSprite>::Create(L"Moninfo8.png", L"Moninfo8.png");

	ResMgr<GameSprite>::Create(L"hud0.png", L"hud0.png");
	ResMgr<GameSprite>::Create(L"hud1.png", L"hud1.png");
	ResMgr<GameSprite>::Create(L"hud2.png", L"hud2.png");

	ResMgr<GameSprite>::Create(L"hud45.png", L"hud45.png", 2, 1);
	ResMgr<GameSprite>::Create(L"hud133.png", L"hud133.png");

	// Sound
	ResMgr<MySound>::SoundLoadFileInDir(L"Sound");

	isLoading = false;
	return 0;
}

TilteLoading::TilteLoading() : isLoading(true)
{
}


TilteLoading::~TilteLoading()
{
}
