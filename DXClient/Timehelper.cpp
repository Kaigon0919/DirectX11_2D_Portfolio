#include "Timehelper.h"
#include<TimeManager.h>

bool Timehelper::Check()
{
	if (m_IsDead)
	{
		return false;
	}

	m_CurTime += TimeManager::GetDeltaTime();

	if (m_CurTime >= m_Time)
	{
		return true;
	}

	return false;
}

void Timehelper::Reset()
{
	m_CurTime = 0.0f;
	m_IsDead = false;
}

Timehelper::Timehelper(float _Time) : m_Time(_Time), m_CurTime(0.0f), m_IsDead(false)
{
}

Timehelper::~Timehelper()
{
}
