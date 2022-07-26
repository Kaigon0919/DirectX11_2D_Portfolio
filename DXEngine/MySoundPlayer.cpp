#include "MySoundPlayer.h"
#include"MySound.h"



bool MySoundPlayer::IsPlay() const
{
	bool isPlaying;
	bool isPaused;
	m_pChannel->isPlaying(&isPlaying);
	m_pChannel->getPaused(&isPaused);
	return isPlaying && !isPaused;
}

void MySoundPlayer::Play(const wchar_t * _SoundName, bool isLoop)
{
	int a = 0;
	if (nullptr != m_pChannel)
	{
		m_pChannel->stop();
	}

	SPTR<MySound> pSound = ResMgr<MySound>::Find(_SoundName);

	assert(nullptr != pSound);

	if (nullptr == pSound)
	{
		return;
	}
	pSound->SetLoop(isLoop);

	MySound::m_pSoundSystem->playSound(pSound->Sound(), nullptr, false, &m_pChannel);
}

void MySoundPlayer::Play()
{
	if (!m_pChannel)
	{
		return;
	}
	if (!IsPlay())
	{
		m_state = SoundState::SP_Stop;
	}
	switch (m_state)
	{
	case SoundState::SP_Play:
		break;
	case SoundState::SP_Pause:
		m_pChannel->setPaused(false);
		break;
	case SoundState::SP_Stop:
		break;
	case SoundState::SP_Max:
		break;
	default:
		break;
	}
	m_state = SP_Play;
}

void MySoundPlayer::Pause()
{
	if (!m_pChannel)
	{
		return;
	}
	m_pChannel->setPaused(true);
	m_state = SP_Pause;
}

void MySoundPlayer::Stop()
{
	m_pChannel->stop();
	m_state = SP_Stop;
}
void MySoundPlayer::ChangeSound(const wchar_t * _SoundFileName, bool isPlay)
{
	if (!IsPlay())
	{
		m_state = SoundState::SP_Stop;
	}
	if (m_state != SP_Stop)
	{
		m_pChannel->stop();
		m_state = SP_Stop;
	}
	SPTR<MySound> pSound = ResMgr<MySound>::Find(_SoundFileName);

	if (nullptr == pSound)
	{
		assert(false && L"Fail change sound");
		return;
	}
	MySound::m_pSoundSystem->playSound(pSound->Sound(), nullptr, !isPlay, &m_pChannel);
	m_pChannel->getPitch(&m_Pitch);
	m_state = isPlay ? SP_Play : SP_Pause;
}

MySoundPlayer::MySoundPlayer() : m_pChannel(nullptr)
{
}


MySoundPlayer::~MySoundPlayer()
{
}
