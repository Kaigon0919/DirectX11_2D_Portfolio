#include "DamageNumber.h"
#include<Render2DSprite.h>
#include<Transform.h>
#include<Camera.h>
#include<TimeManager.h>
void DamageNumber::InitSetting(size_t numberCount, const wchar_t * spriteName, int damage)
{
	m_Value = damage;
	NumberCount = numberCount;
	m_VecRender.reserve(NumberCount);
	m_VecValue.reserve(NumberCount);
	SpriteName = spriteName;

	for (size_t i = 0; i < NumberCount; ++i)
	{
		SPTR<Render2DSprite> newRender = AddComponent<Render2DSprite>(2);
		newRender->SetSprite(spriteName, 0);
		newRender->SetLocalSubScale(newRender->GetSpriteImageSize(0));
		newRender->SetLocalSubPosition(Vector3f(20.0f * i, 0.0f,-10.0f));

		m_VecValue.push_back(0);
		m_VecRender.push_back(newRender);
	}
	ValueToRenderUpdate();
}

void DamageNumber::Update()
{
	if (time_delete.Check())
	{
		GetActor()->Death();
		return;
	}
	GetTransform()->Translate(velocity * TimeManager::GetDeltaTime());
}

void DamageNumber::ValueToRenderUpdate()
{
	size_t tempValue = m_Value;
	int count = 0;
	while (tempValue != 0)
	{
		tempValue /= 10;
		++count;
	}

	if (count > NumberCount)
	{
		for (size_t i = 0; i < NumberCount; ++i)
		{
			m_VecValue[i] = 9;
		}
	}
	else
	{
		int divNumber = 1;
		for (int i = 0; i < count - 1; ++i)
		{
			divNumber *= 10;
		}

		for (int i = 0; i < NumberCount - count; ++i)
		{
			m_VecValue[i] = 0;
			m_VecRender[i]->SetUpdate(false);
		}

		tempValue = m_Value;
		count = (int)NumberCount - count;

		while (count < NumberCount)
		{
			m_VecRender[count]->SetUpdate(true);
			m_VecValue[count] = (int)tempValue / divNumber;
			tempValue -= m_VecValue[count] * divNumber;
			divNumber /= 10;
			++count;
		}
	}

	for (size_t i = 0; i < NumberCount; ++i)
	{
		m_VecRender[i]->SetSprite(SpriteName.c_str(), m_VecValue[i]);
	}
}

DamageNumber::DamageNumber() : time_delete(0.8f)
{
}


DamageNumber::~DamageNumber()
{
}
