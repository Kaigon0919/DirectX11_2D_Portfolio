#pragma once
#include <windows.h>

class TimeManager
{
private:
	TimeManager();
	~TimeManager();
public:
	friend class MainWindow;
private: // private innser class.
	class Timer
	{
	public:
		Timer();
		~Timer();
	private:
		LARGE_INTEGER Count;
		LARGE_INTEGER CurTime;
		LARGE_INTEGER PrevTime;
		float deltaTime;

		int fps;
		int frameCountAcc;
		float fpsTimeAcc;

	public: // Get,Set Function.
		inline float GetDeltaTime()const
		{
			return deltaTime;
		}
		inline int GetFPS()const
		{
			return fps;
		}
	public:
		void Update();
		void FpsUpdate();
	};
private:
	static Timer m_Timer;

public: // Get,Set Function.
	static inline float GetDeltaTime()
	{
		return m_Timer.GetDeltaTime();
	}
	static inline int GetFPS()
	{
		return m_Timer.GetFPS();
	}
private: // public Function.
	static void Update();

};

