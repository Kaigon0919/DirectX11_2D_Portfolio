#include "Hud.h"
#include<Render2DSprite.h>
#include<GameSprite.h>
#include<MainWindow.h>
#include<TimeManager.h>
#include"Player.h"

bool Hud::Init()
{
	SPTR<Transform> Trans = GetComponent<Transform>();
	Trans->SetLocalScale(1.5f, 1.5f, 1.0f);

	Vector2i WinSize = MainWindow::GetSize();

	Vector3f size = Vector3f(Trans->GetWorldScale());

	SPTR<Render2DSprite> Render1;
	Render1 = AddComponent<Render2DSprite>(3);
	Render1->SetSprite(L"hud0.png");
	Render1->SetLocalSubScale(size * Render1->GetSpriteImageSize(0));

	SPTR<Render2DSprite> Render2;
	Render2 = AddComponent<Render2DSprite>(3);
	Render2->SetSprite(L"hud133.png");
	Render2->SetLocalSubScale(size * Render2->GetSpriteImageSize(0));
	Render2->SetLocalSubPosition(size * Vector3f(214.6f,-2.0f, -0.1f));


	SPTR<Render2DSprite> Render3;
	Render3 = AddComponent<Render2DSprite>(3);
	Render3->SetSprite(L"hud45.png");
	Render3->SetLocalSubScale(size * Render3->GetSpriteImageSize(0));
	Render3->SetLocalSubPosition(size * Vector3f(-193.0f, -6.0f, -0.2f));

	SPTR<Render2DSprite> Render4;
	Render4 = AddComponent<Render2DSprite>(3);
	Render4->SetSprite(L"hud45.png",1);
	Render4->SetLocalSubScale(size * Render4->GetSpriteImageSize(0));
	Render4->SetLocalSubPosition(size * Vector3f(178.0f, -7.0f, -0.2f));


	m_HPBar = AddComponent<Render2DSprite>(3);
	m_HPBar->SetSprite(L"hud1.png", 0);
	m_HPBar->SetLocalSubScale(size * m_HPBar->GetSpriteImageSize(0));
	m_HPBar->SetLocalSubPosition(size * Vector3f(-347.0f, 4.0f, -0.2f));
	m_HPBar->SetFillMode(2);

	
	m_MPBar = AddComponent<Render2DSprite>(3);
	m_MPBar->SetSprite(L"hud2.png", 0);
	m_MPBar->SetLocalSubScale(size * m_MPBar->GetSpriteImageSize(0));
	m_MPBar->SetLocalSubPosition(size * Vector3f(348.0f, 4.0f, -0.2f));
	m_MPBar->SetFillMode(2);

	Trans->SetLocalPosition(0.0f, -WinSize.y / 2.0f + ((size * Render1->GetSpriteImageSize(0)).y / 2.0f), -10.0f);
	return true;
}

void Hud::Update()
{
	HPUpdate();
	MPUpdate();
}

void Hud::LateUpdate()
{
}

void Hud::DebugRender()
{
}

void Hud::HPUpdate()
{
	float fill = m_Player->GetCurHP() / m_Player->GetMaxHP();
	if (fill != afterHPFill)
	{
		afterHPFill = fill;
		subHPFill = CurHPFill - afterHPFill;
	}
	if ((CurHPFill - afterHPFill) * subHPFill < 0)
	{
		subHPFill = CurHPFill - afterHPFill;
	}
	CurHPFill -= subHPFill * TimeManager::GetDeltaTime();
	if (fabsf(CurHPFill - afterHPFill) < 0.01)
	{
		subHPFill = 0.0f;
		CurHPFill = afterHPFill;
	}
	m_HPBar->SetFill(CurHPFill);

}

void Hud::MPUpdate()
{
	float fill = m_Player->GetCurMP() / m_Player->GetMaxMP();
	if (fill != afterMPFill)
	{
		afterMPFill = fill;
		subMPFill = CurMPFill - afterMPFill;
	}
	if ((CurMPFill - afterMPFill) * subMPFill < 0)
	{
		subMPFill = CurMPFill - afterMPFill;
	}
	CurMPFill -= subMPFill * TimeManager::GetDeltaTime();
	if (fabsf(CurMPFill - afterMPFill) < 0.01)
	{
		subMPFill = 0.0f;
		CurMPFill = afterMPFill;
	}
	m_MPBar->SetFill(CurMPFill);
}

void Hud::SetPlayer(SPTR<Actor> player)
{
	if (player == nullptr)
	{
		m_Player = nullptr;
	}
	m_Player = player->GetComponent<Player>();
}

Hud::Hud() : CurHPFill(1.0f), afterHPFill(1.0f), subHPFill(0.0f), CurMPFill(1.0f), afterMPFill(1.0f), subMPFill(0.0f)
{
}


Hud::~Hud()
{
}
