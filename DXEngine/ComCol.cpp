#include "ComCol.h"
#include"Level.h"
#include<assert.h>

void ComCol::CallEnter(ComCol * _OtherCol)
{
	itCallStart = m_EnterWorkList.begin();
	itCallEnd = m_EnterWorkList.end();

	for (; itCallStart != itCallEnd; ++itCallStart)
	{
		(*itCallStart)(this, _OtherCol);
	}
}

void ComCol::CallStay(ComCol * _OtherCol)
{
	itCallStart = m_StayWorkList.begin();
	itCallEnd = m_StayWorkList.end();

	for (; itCallStart != itCallEnd; ++itCallStart)
	{
		(*itCallStart)(this, _OtherCol);
	}
}

void ComCol::CallExit(ComCol * _OtherCol)
{
	itCallStart = m_ExitWorkList.begin();
	itCallEnd = m_ExitWorkList.end();

	for (; itCallStart != itCallEnd; ++itCallStart)
	{
		(*itCallStart)(this, _OtherCol);
	}
}

void ComCol::ColRelease()
{
	std::unordered_set<ComCol*>::iterator Start = m_ColSet.begin();
	std::unordered_set<ComCol*>::iterator End = m_ColSet.end();

	for (; Start != End; )
	{
		if (false == (*Start)->IsUpdate())
		{
			CallExit(*Start);
			Start = m_ColSet.erase(Start);
		}
		else {
			++Start;
		}
	}
}

bool ComCol::Init(const wchar_t * _Name)
{
	SetGroupName(_Name);
	ColInit();
	if (true == GetActor()->IsOver())
	{
		std::list<std::wstring> OverList = Level::OverList(GetActor());
		std::list<std::wstring>::iterator StartIter = OverList.begin();
		std::list<std::wstring>::iterator EndIter = OverList.end();

		for (; StartIter != EndIter; ++StartIter)
		{
			SPTR<Level> FindScene = Level::FindLevel((*StartIter).c_str());
			FindScene->CMgr.PushCol(this);
		}
	}
	else
	{
		GetActor()->GetLevel()->CMgr.PushCol(this);
	}
	return true;
}

void ComCol::ColInit()
{
}

bool ComCol::Col(ComCol * _OtherCol)
{
	std::unordered_set<ComCol*>::iterator itFinder = m_ColSet.find(_OtherCol);

	if (ColCheck(_OtherCol))
	{
		if (itFinder == m_ColSet.end())
		{
			m_ColSet.insert(_OtherCol);
			CallEnter(_OtherCol);
		}
		else
		{
			CallStay(_OtherCol);
		}
	}
	else
	{
		if (itFinder != m_ColSet.end())
		{
			CallExit(_OtherCol);
			m_ColSet.erase(_OtherCol);
		}
	}
	return true;
}

ComCol::ComCol(COLTYPE _eType) : m_eType(_eType)
{

}


ComCol::~ComCol()
{
	std::unordered_set<ComCol*>::iterator Start = m_ColSet.begin();
	std::unordered_set<ComCol*>::iterator End = m_ColSet.end();

	for (; Start != End; ++Start)
	{
		CallExit(*Start);
	}
}

