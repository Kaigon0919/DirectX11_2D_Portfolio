#pragma once
#include "SubTransform.h"
#include"Transform.h"
#include"GameMath.h"
#include<functional>
#include<unordered_set>

enum COLTYPE
{
	CT_NONE,
	CT_2DPOINT,
	CT_2DRECT,
	CT_2DCIRCLE,
	CT_2DPOLY, 
	CT_3DRAY, 
	CT_3DSPHERE,
	CT_3DAABB, 
	CT_3DOBB,  
	CT_3DMESH,
	CT_MAX
};


class ComCol : public SubTransform
{
public:
	friend class ColMgr;

protected:
	const COLTYPE m_eType;
	std::wstring m_GroupName;
public:
	const wchar_t* GetGroupName() const
	{
		return m_GroupName.c_str();
	}

	void SetGroupName(const wchar_t* _Name) {
		m_GroupName = _Name;
	}

private:
	std::list<std::function<void(ComCol*, ComCol*)>>::iterator itCallStart;
	std::list<std::function<void(ComCol*, ComCol*)>>::iterator itCallEnd;

	std::list<std::function<void(ComCol*, ComCol*)>> m_EnterWorkList;
	std::list<std::function<void(ComCol*, ComCol*)>> m_StayWorkList;
	std::list<std::function<void(ComCol*, ComCol*)>> m_ExitWorkList;

private:
	void CallEnter(ComCol* _OtherCol);
	void CallStay(ComCol* _OtherCol);
	void CallExit(ComCol* _OtherCol);
	virtual void ColDataUpdate() {}

	void ColRelease();

public:
	template<class T>
	void PushEnterFunc(void(T::*pFunc)(ComCol*, ComCol*), T* _Object)
	{
		std::function<void(ComCol*, ComCol*)> Func = std::bind(pFunc, _Object, std::placeholders::_1, std::placeholders::_2);
		if (Func == nullptr)
		{
			assert(false && L"Fail Push EnterFunc");
			return;
		}
		m_EnterWorkList.push_back(Func);
	}
	template<class T>
	void PushStayFunc(void(T::*pFunc)(ComCol*, ComCol*), T* _Object)
	{
		std::function<void(ComCol*, ComCol*)> Func = std::bind(pFunc, _Object, std::placeholders::_1, std::placeholders::_2);
		if (Func == nullptr)
		{
			assert(false && L"Fail Push StayFunc");
			return;
		}
		m_StayWorkList.push_back(Func);
	}
	template<class T>
	void PushExitFunc(void(T::*pFunc)(ComCol*, ComCol*), T* _Object)
	{
		std::function<void(ComCol*, ComCol*)> Func = std::bind(pFunc, _Object, std::placeholders::_1, std::placeholders::_2);
		if (Func == nullptr)
		{
			assert(false && L"Fail Push ExitFunc");
			return;
		}
		m_ExitWorkList.push_back(Func);
	}
public:
	inline COLTYPE GetColType() { return m_eType; }

private:
	std::unordered_set<ComCol*> m_ColSet;

public:
	bool Init(const wchar_t * _Name = L"Default");
protected:
	virtual void ColInit();

public:
	virtual bool Col(ComCol* _OtherCol);
	virtual bool ColCheck(ComCol* _OtherCol) = 0;

protected:
	ComCol(COLTYPE _eType);
	~ComCol();
};

