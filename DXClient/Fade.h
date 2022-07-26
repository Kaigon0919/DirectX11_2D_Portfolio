#pragma once
#include<Component.h>
class RenderFillRect;
class Fade : public Component
{
private:
	float m_FadeTime;
	float m_Amount;
	bool m_bFade;
	SPTR<RenderFillRect> m_Render;
public:

	void FadeIn()
	{
		m_bFade = true;
	}
	void FadeOut()
	{
		m_bFade = false;
	}
	bool IsFade()const
	{
		return m_bFade;
	}
	void SetFadeTime(float time)
	{
		m_FadeTime = time;
	}
	bool IsFadeInComplete()const
	{
		return m_Amount <= -0.1f;
	}
	bool IsFadeOutComplete()const
	{
		return m_Amount >= 1.1f;
	}
	void SetAmount(float value)
	{
		m_Amount = value;
	}
	bool Init() override;
	void Update() override;
public:
	Fade();
	~Fade();
};

