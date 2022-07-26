#pragma once
#include"Resource.h"
#include"ResMgr.h"
#include<FMOD\inc\fmod.hpp>

#ifdef _WIN64
#pragma comment(lib,"FMOD\\lib\\fmod64_vc.lib")
#else
#pragma comment(lib,"FMOD\\lib\\fmod_vc.lib")
#endif


class MySound : public Resource
{
public:
	friend class MySoundPlayer;
	friend class SystemCore;

private:
	class Destroy
	{
	public:
		~Destroy()
		{
			MySound::SoundDestroy();
		}
	};
	friend MySound::Destroy;
	static Destroy Des;

private:
	static FMOD::System* m_pSoundSystem;

private:
	static void SoundInit();
	static void SoundDestroy();

private:
	FMOD::Sound* m_pSound;
	UINT Len;

public:
	DEFLOADER(MySound, std::wstring)
		DEFPATHLOADERFUNC()
		DEFPATHLOADERFUNCPARA()
		DEFLOADEREND

public:
	FMOD::Sound* Sound()
	{
		return m_pSound;
	}


public:
	bool Load();
public:
	void SetLoop(bool isLoop);
public:
	MySound();
	~MySound();
};

