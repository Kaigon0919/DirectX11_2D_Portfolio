#pragma once
#include "Component.h"
#include <FMOD\inc\fmod.hpp>
class MySoundPlayer : public Component
{
private:
	enum SoundState
	{
		SP_Play,
		SP_Pause,
		SP_Stop,
		SP_Max
	};
private:
	FMOD::Channel* m_pChannel;
	float m_Pitch;
	SoundState m_state;
public:
	inline float GetPitch()const
	{
		return m_Pitch;
	}
	inline void SetPitch(float _PitchValue)
	{
		m_Pitch = _PitchValue;
		m_pChannel->setPitch(m_Pitch);
	}
	bool IsPlay()const;

public:
	void Play(const wchar_t* _SoundName , bool isLoop = false);
	void Play();
	void Pause();
	void Stop();
	void ChangeSound(const wchar_t * _SoundFileName, bool isPlay = false);

public:
	MySoundPlayer();
	~MySoundPlayer();
};

