#include "TimeManager.h"

TimeManager::Timer TimeManager::m_Timer;


TimeManager::TimeManager()
{
}

TimeManager::~TimeManager()
{
}

void TimeManager::Update()
{
	m_Timer.Update();
	m_Timer.FpsUpdate();
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Timer Function.
// 
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

TimeManager::Timer::Timer() : Count(), CurTime(), PrevTime(), deltaTime(0), fps(0), frameCountAcc(0), fpsTimeAcc(0.0f)
{
	// Cpu가 1초 동안 셀 수 있는 Count를 가져온다.
	QueryPerformanceFrequency(&Count);

	// Cpu가 지금까지 누적한 Count를 가져온다.
	QueryPerformanceCounter(&CurTime);
	PrevTime = CurTime;

}

TimeManager::Timer::~Timer()
{}

void TimeManager::Timer::Update()
{
	QueryPerformanceCounter(&CurTime);
	// (현재 프레임 누적 갯수 - 전 프레임 누적갯수) / 1초 동안 셀수 있는 갯수 = 전 프레임과 현 프레임의 시간 차.
	deltaTime = (CurTime.QuadPart - PrevTime.QuadPart) / (float)Count.QuadPart;
	PrevTime = CurTime;
}

void TimeManager::Timer::FpsUpdate()
{
	// 프레임 누적.
	++frameCountAcc;

	// 시간 누적.
	fpsTimeAcc += deltaTime;

	// 1초가 지났다면.
	if (fpsTimeAcc >= 1.0f)
	{
		// Frame per second => Frame / sec
		fps = (int)(frameCountAcc / fpsTimeAcc);
		frameCountAcc = 0;
		fpsTimeAcc = 0.0f; // Line 54 에서 1로 나눴으면 - 1.0 을 해주면 되지만 fpsTimeAcc를 나눔으로 0으로한다.
	}
}
