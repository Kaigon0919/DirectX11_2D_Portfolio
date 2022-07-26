#include "SeriaRoom.h"

#include"Player.h"
#include"Hud.h"
#include"Gate.h"
#include"BackGround.h"

#include<MainWindow.h>
#include<Transform.h>
#include<Camera.h>
#include<Col2DRect.h>
#include<DxDebug.h>
#include<MySoundPlayer.h>
#include"Fade.h"

bool SeriaRoom::Loading()
{
	// Render Sort.
	GetLevel()->RMgr.YSortOn(1);
	GetLevel()->RMgr.ZSortOn(3);

	// Camera Setting.
	// Main.
	m_Camera = GetLevel()->CreateActor(L"Camera");
	SPTR<Camera> comCamera = m_Camera->AddComponent<Camera>();
	m_Camera->GetTransform()->SetLocalPosition(0.0f, 0.0f, -100.0f);
	comCamera->OnViewGroup(0, 1 , 2);
	comCamera->SetZoom(1.0f);

	// Main Camera Size Setting.
	Vector2i size = MainWindow::GetSize() / 1.5f;
	comCamera->SetOrthSizeMode(Camera::ORTH_SIZE_MODE::ORTH_SIZE_FREE, size);

	// UI Cmaera Setting.
	m_UICamera = GetLevel()->CreateActor(L"UICamera");
	SPTR<Camera> UICamera = m_UICamera->AddComponent<Camera>();
	m_UICamera->GetTransform()->SetLocalPosition(0.0f, 0.0f, -100.0f);
	UICamera->OnViewGroup(3,4);
	UICamera->SetZoom(1.0f);

	// Mouse Setting.
	m_Mouse = GetLevel()->CreateActor(L"Mouse");
	SPTR<Col2DRect> rect = m_Mouse->AddComponent<Col2DRect>();
	m_Mouse->GetTransform()->SetLocalScale(Vector3f(10.0f, 10.0f, 10.0f));

	// BackGround Setting.
	m_Background = GetLevel()->CreateActor(L"Background");
	SPTR<BackGround> backCom = m_Background->AddComponent<BackGround>();
	backCom->DataLoad(L"SeriaRoom.data");

	// Player Setting.
	m_Player = GetLevel()->CreateActor(L"Player");
	m_ComPlayer = m_Player->AddComponent<Player>();
	// UI Actor Setting.
	SPTR<Actor> UIActor = GetLevel()->CreateActor(L"UIHud");
	SPTR<Hud> UIHud = UIActor->AddComponent<Hud>();
	UIHud->SetPlayer(m_Player);

	// OverActor Setting.
	m_Player->OverActor(L"Village", L"Stage1", L"Stage2",L"StageBoss");
	UIActor->OverActor(L"Village", L"Stage1", L"Stage2", L"StageBoss");
	
	// Fade
	SPTR<Actor> FadeActor = GetLevel()->CreateActor(L"fade");
	m_Fade = FadeActor->AddComponent<Fade>();
	m_Fade->FadeOut();
	backCom->SetFade(m_Fade);
	return true;
}

void SeriaRoom::Start()
{
	// Player Setting.
	if (m_Player != nullptr)
	{
		m_ComPlayer = m_Player->GetComponent<Player>();
		SPTR<Camera> comCamera = m_Camera->GetComponent<Camera>();
		m_ComPlayer->SetCamera(comCamera);
		m_ComPlayer->SetBackground(m_Background.Get());
		m_ComPlayer->SetBattle(false);
		// Sound.
		m_ComPlayer->SetBackSound(L"seria_gate.ogg");
	}
	m_ComPlayer->SetFade(m_Fade);
	m_Fade->FadeIn();
}

void SeriaRoom::Update()
{
	Vector2f mousePos = GetLevel()->GetMainCamera()->ScreenToClient(InputManager::GetMousePos());
	m_Mouse->GetTransform()->SetWorldPosition(Vector3f(mousePos.x,mousePos.y,0.0f));

	m_ComPlayer->AddHP(3.0f * TimeManager::GetDeltaTime());
	m_ComPlayer->AddMP(3.0f * TimeManager::GetDeltaTime());
	
}

void SeriaRoom::LateUpdate()
{
}

void SeriaRoom::End()
{
}

void SeriaRoom::DebugRender()
{

	wchar_t DebugOutText[1024];

	Vector3f PlayerWorld = m_Player->GetTransform()->GetWorldPosition();
	swprintf_s(DebugOutText, L"Player WorldPosotion : ( x : %f , y : %f , z : %f )", PlayerWorld.x, PlayerWorld.y, PlayerWorld.z);
	DxDebug::DrawStr(DebugOutText, 16, Vector2i(10, 10), Color4f(0.0f, 0.0f, 0.0f));

	SPTR<Player> ComPlayer= m_Player->GetComponent<Player>();
	Vector3f PlayerVirtualPos = ComPlayer->GetVirtualPosition();
	swprintf_s(DebugOutText, L"Player VirtualPosotion : ( x : %f , y : %f, z : %f )", PlayerVirtualPos.x, PlayerVirtualPos.y, PlayerVirtualPos.z);
	DxDebug::DrawStr(DebugOutText, 16, Vector2i(10, 30), Color4f(0.0f, 0.0f, 0.0f));

	if (GetLevel()->GetMainCamera() != nullptr)
	{
		Vector2i mousePos = GetLevel()->GetMainCamera()->ScreenToClient(InputManager::GetMousePos());
		swprintf_s(DebugOutText, L"MousePos: ( x : %d , y : %d)", mousePos.x, mousePos.y);
		DxDebug::DrawStr(DebugOutText, 16, Vector2i(10, 50), Color4f(0.0f, 0.0f, 0.0f));
	}
}


SeriaRoom::SeriaRoom()
{
}


SeriaRoom::~SeriaRoom()
{
}
