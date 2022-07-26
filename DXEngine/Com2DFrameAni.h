#pragma once
#include "Component.h"
#include<unordered_map>
#include<functional>
#include<vector>
class Render2DSprite;
class Com2DFrameAni : public Component
{
public:
	enum EVENTTYPE
	{
		STAY,
		CHANGEEND,
		CHANGESTART,
		CHANGEENDSTART,
		CHANGEENDSTARTSTAY,
	};
	struct AniData
	{
		std::wstring AniName;
		unsigned int StartFrame;
		unsigned int EndFrame;
		float DefTime;
		bool isLoop;
		std::list<void*> Event;
	};
private:
	class FrameEvent : public IRefCount
	{
	public:
		EVENTTYPE m_eType;
		unsigned int m_StartFrame;
		unsigned int m_EndFrame;
		void * m_EventData;
		std::function<void(void*)> m_Event;
	public:
		void EventCheck(unsigned int _PrevIndex, unsigned int _NextIndex);
	};
	class FrameAni : public IRefCount, public IName
	{
	public:
		unsigned int m_CurFrame;
		unsigned int m_Start;
		unsigned int m_End;
		float m_CurTime;
		bool m_bLoop;
		bool m_bEnd;
	public:
		std::vector<float> m_Time;
		std::vector<SPTR<FrameEvent>> m_Event;

	public:
		void Init();
		unsigned int Update();
		void EventCheck(unsigned int _PrevIndex, unsigned int _NextIndex);
		void DeleteEvent(int idx);
		int FindEventIndex(unsigned int _StartFrame, unsigned int _EndFrame);
	};

private:
	SPTR<Render2DSprite> m_Render;
	std::unordered_map<std::wstring, SPTR<FrameAni>> m_AniMap;
	SPTR<FrameAni> m_CurAni;

public:
	SPTR<FrameAni> FindAni(const wchar_t* _AniName);
	void CreateAni(const wchar_t* _AniName, unsigned int _StartFrame, unsigned int _EndFrame, float _FrameTime = 0.1f, bool _bLoop = true);
	void CreateAni(const wchar_t* _AniName, unsigned int _StartFrame, unsigned int _EndFrame, bool _bLoop, float _FrameTime = 0.1f);
	void DeleteAni(const wchar_t* _AniName);
	void ChangeAni(const wchar_t* _AniName, unsigned int _StartFrame = 0);
	void SetFrameTime(const wchar_t* _AniName, unsigned int _Frame, float _FrameTime);
	void Clear();
public:
	template<class T>
	void SetFrameEvent(const wchar_t* _AniName, unsigned int _StartFrame, unsigned int _EndFrame, void(T::*pFunc)(void*), T* _Obj, void* m_EventData = nullptr, EVENTTYPE _eType = EVENTTYPE::CHANGEEND)
	{
		SPTR<FrameAni> FindPtr = FindAni(_AniName);

		if (nullptr == FindPtr)
		{
			assert(false && L"Not find ani");
		}

		SPTR<FrameEvent> NewFrame = new FrameEvent();

		NewFrame->m_StartFrame = _StartFrame;
		NewFrame->m_EndFrame = _EndFrame;
		NewFrame->m_eType = _eType;
		NewFrame->m_EventData = m_EventData;

		std::function<void(void*)> EventFunc = std::bind(pFunc, _Obj, std::placeholders::_1);
		if (nullptr == EventFunc)
		{
			assert(false && L"Fail, Create EventFunc");
			return;
		}
		NewFrame->m_Event = EventFunc;
		FindPtr->m_Event.push_back(NewFrame);
	}
	void DeleteEvent(const wchar_t *_AniName, int idx);
	int FindEventIndex(const wchar_t *_AniName, unsigned int _StartFrame, unsigned int _EndFrame);
public:
	bool Init() override;
	void FixUpdate() override;
	bool IsAniEnd()const {
		if (m_CurAni == nullptr)
		{
			return true;
		}
		return m_CurAni->m_bEnd;
	}

	std::wstring CurAniName()
	{
		return m_CurAni->GetName();
	}
	bool IsCurAniName(std::wstring value)
	{
		return m_CurAni->GetName() == value;
	}
	float CurAniPer()
	{
		float den = m_CurAni->m_End - m_CurAni->m_Start+1.0f;
		float cur = m_CurAni->m_CurFrame - m_CurAni->m_Start + 1.0f;
		return cur/den;
	}
	size_t GetCurIndex()const
	{
		if (m_CurAni == nullptr)
		{
			return 0;
		}
		return m_CurAni->m_CurFrame;
	}
public:
	std::list<AniData> IOAllData();
	AniData GetAniData(const wchar_t * _aniName)const;
public:
	Com2DFrameAni();
	~Com2DFrameAni();
};

