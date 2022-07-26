#include "MySound.h"
FMOD::System* MySound::m_pSoundSystem = nullptr;
MySound::Destroy MySound::Des;

void MySound::SoundInit()
{
	FMOD::System_Create(&m_pSoundSystem);
	assert(nullptr != m_pSoundSystem);

	if (nullptr == m_pSoundSystem)
	{
		return;
	}

	// 최대 동시에 1000개 이상를 재생할수 있다.
	FMOD_RESULT Return = m_pSoundSystem->init(32, FMOD_DEFAULT, nullptr);
	assert(FMOD_OK == Return);
}

void MySound::SoundDestroy()
{
	if (nullptr != m_pSoundSystem)
	{
		m_pSoundSystem->release();
	}
}

bool MySound::Load()
{
	std::string MPath = CW2A(GetPath().c_str());

	if (FMOD_OK != m_pSoundSystem->createSound(MPath.c_str(), FMOD_DEFAULT, nullptr, &m_pSound))
	{
		assert(false);
		return false;
	}

	assert(nullptr != m_pSound);

	if (nullptr == m_pSound)
	{
		return false;
	}

	m_pSound->getLength(&Len, FMOD_TIMEUNIT_MS);

	return true;
}

void MySound::SetLoop(bool isLoop)
{
	FMOD_MODE mode = FMOD_LOOP_OFF;
	if (isLoop)
	{
		mode = FMOD_LOOP_NORMAL;
	}
	m_pSound->setMode(mode);

}

MySound::MySound() : Len(0), m_pSound(nullptr)
{
}


MySound::~MySound()
{
}
