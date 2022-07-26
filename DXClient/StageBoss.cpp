#include "StageBoss.h"
#include<Camera.h>
#include<MainWindow.h>
#include"BackGround.h"
#include"MonsterMgr.h"
#include"Player.h"
#include"Fade.h"
bool StageBoss::Loading()
{
	// Render Sort.
	GetLevel()->RMgr.YSortOn(1);
	GetLevel()->RMgr.ZSortOn(3);

	// Camera Setting.
	// Main.
	m_Camera = GetLevel()->CreateActor(L"Camera");
	SPTR<Camera> comCamera = m_Camera->AddComponent<Camera>();
	m_Camera->GetTransform()->SetLocalPosition(0.0f, 0.0f, -100.0f);
	comCamera->OnViewGroup(0, 1, 2);
	comCamera->SetZoom(1.0f);

	// Main Camera Size Setting.
	Vector2i size = MainWindow::GetSize() / 1.5f;
	comCamera->SetOrthSizeMode(Camera::ORTH_SIZE_MODE::ORTH_SIZE_FREE, size);

	// UI Cmaera Setting.
	m_UICamera = GetLevel()->CreateActor(L"UICamera");
	SPTR<Camera> UICamera = m_UICamera->AddComponent<Camera>();
	m_UICamera->GetTransform()->SetLocalPosition(0.0f, 0.0f, -100.0f);
	UICamera->OnViewGroup(3);
	UICamera->SetZoom(1.0f);

	// BackGround Setting.
	m_Background = GetLevel()->CreateActor(L"Background");
	SPTR<BackGround> backCom = m_Background->AddComponent<BackGround>();
	backCom->DataLoad(L"StageBoss.data");
	backCom->CloseGate();

	// Monster Setting.
	SPTR<Actor> MonMgrActor = GetLevel()->CreateActor(L"MonsterMgr");
	m_MonMgr = MonMgrActor->AddComponent<MonsterMgr>();
	m_MonMgr->LoadMonBat(L"StageBoss_mon.data");
	m_MonMgr->SetBackground(m_Background.Get());
	// Fade
	SPTR<Actor> FadeActor = GetLevel()->CreateActor(L"fade");
	m_Fade = FadeActor->AddComponent<Fade>();
	m_Fade->FadeOut();
	backCom->SetFade(m_Fade);
	return true;
}

void StageBoss::Start()
{
	// Player Setting.
	if (m_Player == nullptr)
	{
		m_Player = GetLevel()->FindActor(L"Player");
		if (m_Player == nullptr)
		{
			assert(false);
		}
	}
	m_ComPlayer = m_Player->GetComponent<Player>();
	SPTR<Camera> comCamera = m_Camera->GetComponent<Camera>();
	m_ComPlayer->SetCamera(comCamera);
	m_ComPlayer->SetBackground(m_Background.Get());

	// MonMgr.
	if (m_Player != nullptr)
	{
		m_MonMgr->SetPlayer(m_ComPlayer);
		if (!m_MonMgr->MonAllDeath())
		{
			m_ComPlayer->SetBattle(true);
		}
	}
	// Sound.
	m_ComPlayer->SetBackSound(L"1st_spine_boss.ogg");
	m_ComPlayer->SetFade(m_Fade);
	m_Fade->FadeIn();
}

void StageBoss::Update()
{
	if (m_MonMgr->MonAllDeath())
	{
		SPTR<Player> m_ComPlayer = m_Player->GetComponent<Player>();
		m_ComPlayer->SetBattle(false);

		SPTR<BackGround> backCom = m_Background->GetComponent<BackGround>();
		backCom->OpenGate();
	}
}

void StageBoss::LateUpdate()
{
}

void StageBoss::End()
{
}

void StageBoss::DebugRender()
{
}

StageBoss::StageBoss()
{
}


StageBoss::~StageBoss()
{
}
