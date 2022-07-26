#pragma once
class Timehelper
{
private:
	float m_Time;
	float m_CurTime;
	bool m_IsDead;
public:
	bool Check();
	void Reset();
	inline void SetDead(bool isdead)
	{
		m_IsDead = isdead;
	}
	inline void SetTime(float time)
	{
		m_Time = time;
	}
public:
	Timehelper(float _Time = 0.0f);
	~Timehelper();
};

