#include "Com2DFrameAni.h"
#include"TimeManager.h"
#include"Render2DSprite.h"
#include"STLHelper.h"
#include<assert.h>

SPTR<Com2DFrameAni::FrameAni> Com2DFrameAni::FindAni(const wchar_t * _AniName)
{
	return MapFindHelper<SPTR<FrameAni>>(m_AniMap,_AniName);
}

void Com2DFrameAni::CreateAni(const wchar_t * _AniName, unsigned int _StartFrame, unsigned int _EndFrame, float _FrameTime, bool _bLoop)
{
	if (nullptr != FindAni(_AniName))
	{
		assert(false && L"Ani already exists");
		return;
	}

	SPTR<FrameAni> ani = new FrameAni();

	ani->SetName(_AniName);
	ani->m_bLoop = _bLoop;
	ani->m_Start = _StartFrame;
	ani->m_End = _EndFrame;
	for (size_t i = 0; i < _EndFrame - _StartFrame + 1; ++i)
	{
		ani->m_Time.push_back(_FrameTime);
	}
	m_AniMap.insert(std::unordered_map<std::wstring, SPTR<FrameAni>>::value_type(ani->GetName(), ani));
}

void Com2DFrameAni::CreateAni(const wchar_t * _AniName, unsigned int _StartFrame, unsigned int _EndFrame, bool _bLoop, float _FrameTime)
{
	CreateAni(_AniName, _StartFrame, _EndFrame, _FrameTime, _bLoop);
}

void Com2DFrameAni::ChangeAni(const wchar_t * _AniName, unsigned int _StartFrame)
{
	m_CurAni = FindAni(_AniName);
	m_CurAni->Init();
}

void Com2DFrameAni::DeleteAni(const wchar_t * _AniName)
{
	std::unordered_map<std::wstring, SPTR<FrameAni>>::iterator taget = m_AniMap.find(_AniName);
	if (taget == m_AniMap.end())
	{
		assert(false && L"Not find taget, Delete Ani");
	}
	m_AniMap.erase(taget);
}

void Com2DFrameAni::Clear()
{
	m_AniMap.clear();
}

void Com2DFrameAni::SetFrameTime(const wchar_t * _AniName, unsigned int _Frame, float _FrameTime)
{
	SPTR<FrameAni> FindPtr = FindAni(_AniName);

	if (nullptr == FindPtr)
	{
		assert(false && L"Not find Ani");
	}
	FindPtr->m_Time[_Frame - FindPtr->m_Start] = _FrameTime;
}

bool Com2DFrameAni::Init()
{
	m_Render = GetComponent<Render2DSprite>();
	if (m_Render == nullptr)
	{
		assert(false && L"Com2DFrameAni, Fail GetComponent Render2DSprite");
		return false;
	}
	return true;
}

void Com2DFrameAni::FixUpdate()
{
	if (m_CurAni != nullptr)
	{
		m_Render->SetSpriteIndex(m_CurAni->Update());
	}
}

std::list<Com2DFrameAni::AniData> Com2DFrameAni::IOAllData()
{
	std::unordered_map<std::wstring, SPTR<FrameAni>>::iterator StartIter = m_AniMap.begin();
	std::unordered_map<std::wstring, SPTR<FrameAni>>::iterator EndIter = m_AniMap.end();

	std::list<AniData> list;

	for (; StartIter != EndIter; ++StartIter)
	{
		AniData Info;
		Info.AniName = (StartIter->first);
		Info.StartFrame = StartIter->second->m_Start;
		Info.EndFrame = StartIter->second->m_End;
		Info.DefTime = StartIter->second->m_Time[0];
		Info.isLoop = StartIter->second->m_bLoop;


		std::vector<SPTR<FrameEvent>>* ptr = &StartIter->second->m_Event;
		int eventNum = (int)ptr->size();
		Info.Event;

		for (int i = 0; i < eventNum; ++i)
		{
			if (ptr->at(i)->m_EventData == nullptr)
			{
				continue;
			}
			Info.Event.push_back(ptr->at(i)->m_EventData);
		}
		list.push_back(Info);
	}
	return list;
}

Com2DFrameAni::AniData Com2DFrameAni::GetAniData(const wchar_t * _aniName) const
{
	SPTR<FrameAni> ptr = (m_AniMap.find(_aniName)->second);

	AniData data;
	data.AniName = _aniName;
	data.DefTime = ptr->m_Time[0];
	data.StartFrame = ptr->m_Start;
	data.EndFrame = ptr->m_End;
	data.isLoop = ptr->m_bLoop;

	int eventNum = (int)ptr->m_Event.size();

	for (int i = 0; i < eventNum; ++i)
	{
		if (ptr->m_Event[i]->m_EventData == nullptr)
		{
			continue;
		}
		data.Event.push_back(ptr->m_Event[i]->m_EventData);
	}
	return data;
}

void Com2DFrameAni::DeleteEvent(const wchar_t *_AniName,int idx)
{
	std::unordered_map<std::wstring, SPTR<FrameAni>>::iterator taget = m_AniMap.find(_AniName);
	if (taget == m_AniMap.end())
	{
		assert(false && L"Not find taget");
	}
	taget->second->DeleteEvent(idx);
}
int Com2DFrameAni::FindEventIndex(const wchar_t * _AniName, unsigned int _StartFrame, unsigned int _EndFrame)
{
	std::unordered_map<std::wstring, SPTR<FrameAni>>::iterator taget = m_AniMap.find(_AniName);
	if (taget == m_AniMap.end())
	{
		assert(false && L"Not find taget");
	}
	return taget->second->FindEventIndex(_StartFrame,_EndFrame);
}
Com2DFrameAni::Com2DFrameAni() : m_CurAni(nullptr)
{
}


Com2DFrameAni::~Com2DFrameAni()
{
}

//////////////////////////////////////////////////////////////////////////
// FrameAni
void Com2DFrameAni::FrameAni::Init()
{
	m_CurFrame = m_Start;
	m_CurTime = m_Time[0];
	m_bEnd = false;

}

unsigned int Com2DFrameAni::FrameAni::Update()
{
	if (m_CurFrame == m_End && false == m_bLoop)
	{
		m_bEnd = true;
		return m_End;
	}

	m_bEnd = false;
	m_CurTime -= TimeManager::GetDeltaTime();

	if (0.0f >= m_CurTime)
	{
		++m_CurFrame;

		// 증가 할때만 체크한다.
		if (m_CurFrame > m_End)
		{
			m_bEnd = true;

			if (true == m_bLoop)
			{
				m_bEnd = true;
				m_CurFrame = m_Start;
				m_CurTime = m_Time[m_CurFrame - m_Start];
				EventCheck(m_End, m_Start);
			}
		}
		else
		{
			m_CurTime = m_Time[m_CurFrame - m_Start];
			EventCheck(m_CurFrame - 1, m_CurFrame);
		}

	}
	return m_CurFrame;
}

void Com2DFrameAni::FrameAni::EventCheck(unsigned int _PrevIndex, unsigned int _NextIndex)
{
	std::vector<SPTR<FrameEvent>>::iterator m_StartIter = m_Event.begin();
	std::vector<SPTR<FrameEvent>>::iterator m_EndIter = m_Event.end();

	for (; m_StartIter != m_EndIter; ++m_StartIter)
	{
		(*m_StartIter)->EventCheck(_PrevIndex, _NextIndex);
	}
}

void Com2DFrameAni::FrameAni::DeleteEvent(int idx)
{
	if (idx < 0 || idx >= m_Event.size())
		return;
	m_Event.erase(m_Event.begin() + idx);
}
int Com2DFrameAni::FrameAni::FindEventIndex(unsigned int _StartFrame, unsigned int _EndFrame)
{
	for (size_t i = 0; i < m_Event.size(); ++i)
	{
		if (m_Event[i]->m_StartFrame == _StartFrame && m_Event[i]->m_EndFrame == _EndFrame)
		{
			return (int)i;
		}
	}
	return -1;
}
// Event.
void Com2DFrameAni::FrameEvent::EventCheck(unsigned int _PrevIndex, unsigned int _NextIndex)
{
	if (m_StartFrame <= _NextIndex && m_EndFrame >= _NextIndex)
	{
		if (nullptr != m_Event)
		{
			m_Event(m_EventData);
		}
	}
}