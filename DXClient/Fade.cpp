#include "Fade.h"
#include<TimeManager.h>
#include<RenderFillRect.h>
#include<Level.h>
#include<Camera.h>
#include<MainWindow.h>
bool Fade::Init()
{
	SPTR<Camera> cam = GetActor()->GetLevel()->GetMainCamera();
	float ZValue = cam->GetTransform()->GetWorldPosition().z;
	GetTransform()->SetWorldPosition(0.0f, 0.0f, ZValue + 1.0f);

	Vector3f Size = MainWindow::GetSize();
	Size.z = 1.0f;
	m_Render = AddComponent<RenderFillRect>(3);
	m_Render->SetLocalSubScale(Size);
	return true;
}
void Fade::Update()
{
	if (m_bFade)
	{
		m_Amount -= (1.2f / m_FadeTime) * TimeManager::GetDeltaTime();
		m_Amount = m_Amount < -0.2f ? -0.2f : m_Amount;
	}
	else
	{
		m_Amount += (1.2f / m_FadeTime) * TimeManager::GetDeltaTime();
		m_Amount = m_Amount > 1.2f ? 1.2f : m_Amount;
	}
	m_Render->SetFillColor(Color4f(0.0f, 0.0f, 0.0f, m_Amount));
}

Fade::Fade() : m_Amount(1.2f), m_FadeTime(1.0f)
{
}


Fade::~Fade()
{
}
