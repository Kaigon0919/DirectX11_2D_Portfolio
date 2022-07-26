#include "ColMgr.h"
#include"STLHelper.h"
#include<assert.h>

void ColMgr::ColLink(const wchar_t * left, const wchar_t* right)
{
	SPTR<ColGroup> leftPtr = MapFindHelper<SPTR<ColGroup>>(m_ColMap, left);
	SPTR<ColGroup> rightPtr = MapFindHelper<SPTR<ColGroup>>(m_ColMap, right);

	if (leftPtr == nullptr)
	{
		leftPtr = CreateGroup(left);
	}
	if (rightPtr == nullptr)
	{
		rightPtr = CreateGroup(right);

	}


	std::list<ColGroup*>::iterator itListStart = leftPtr->m_Other.begin();
	std::list<ColGroup*>::iterator itListEnd = leftPtr->m_Other.end();

	for (; itListStart != itListEnd; ++itListStart)
	{
		if (rightPtr.Get() == (*itListStart))
		{
			return;
		}
	}

	leftPtr->m_Other.push_back(rightPtr.Get());
}

void ColMgr::PushCol(ComCol * _Col)
{
	SPTR<ColGroup> Ptr = MapFindHelper<SPTR<ColGroup>>(m_ColMap, _Col->GetGroupName());

	if (Ptr == nullptr)
	{
		Ptr = CreateGroup(_Col->GetGroupName());
	}

	Ptr->PushCol(_Col);
}

SPTR<ColMgr::ColGroup> ColMgr::CreateGroup(const wchar_t * _Name)
{
	return m_ColMap.insert(std::unordered_map<std::wstring, SPTR<ColGroup>>::value_type(_Name, new ColGroup())).first->second;
}

void ColMgr::Release()
{
	std::unordered_map<std::wstring, SPTR<ColGroup>>::iterator Start = m_ColMap.begin();
	std::unordered_map<std::wstring, SPTR<ColGroup>>::iterator End = m_ColMap.end();
	for (; Start != End; ++Start)
	{
		Start->second->Release();
	}
}

void ColMgr::Col()
{
	std::unordered_map<std::wstring, SPTR<ColGroup>>::iterator Start = m_ColMap.begin();
	std::unordered_map<std::wstring, SPTR<ColGroup>>::iterator End = m_ColMap.end();

	for (; Start != End; ++Start)
	{
		Start->second->ColDataUpdate();
	}

	Start = m_ColMap.begin();
	End = m_ColMap.end();

	for (; Start != End; ++Start)
	{
		Start->second->Col();
	}
}

void ColMgr::DebugRender()
{
	std::unordered_map<std::wstring, SPTR<ColGroup>>::iterator Start = m_ColMap.begin();
	std::unordered_map<std::wstring, SPTR<ColGroup>>::iterator End = m_ColMap.end();

	for (; Start != End; ++Start)
	{
		Start->second->DebugRender();
	}
}

bool ColMgr::IsHasCol(const ComCol * const comCol)
{
	if (comCol == nullptr)
	{
		assert(false);
		return false;
	}
	SPTR<ColGroup> Ptr = MapFindHelper<SPTR<ColGroup>>(m_ColMap, comCol->GetGroupName());
	//std::unordered_map<std::wstring, SPTR<ColGroup>>::iterator itFinder = m_ColMap.find(comCol->GetGroupName());
	if (Ptr == nullptr)
	{
		return false;
	}
	else
	{
		std::list<SPTR<ComCol>>::iterator itListStart = Ptr->m_ColList.begin();
		std::list<SPTR<ComCol>>::iterator itListEnd = Ptr->m_ColList.end();

		for (; itListStart != itListEnd; ++itListStart)
		{
			if ((*itListStart) == comCol)
			{
				return true;
			}
		}
	}
	return false;
}

ColMgr::ColMgr()
{
}


ColMgr::~ColMgr()
{
}

/////////////////////////////////////////////////////////////////////////////////////////
// ColGroup

void ColMgr::ColGroup::PushCol(ComCol * _Col)
{
	m_ColList.push_back(_Col);
}

void ColMgr::ColGroup::Col()
{
	std::list<ColGroup*>::iterator ColStart = m_Other.begin();
	std::list<ColGroup*>::iterator ColEnd = m_Other.end();

	for (; ColStart != ColEnd; ++ColStart)
	{
		if (this != (*ColStart))
		{
			OtherCol((*ColStart));
		}
		else {
			// 자기와 같은 그룹이 충돌시.
			ThisCol();
		}
	}
}

void ColMgr::ColGroup::Release()
{
	std::list<SPTR<ComCol>>::iterator ColStart = m_ColList.begin();
	std::list<SPTR<ComCol>>::iterator ColEnd = m_ColList.end();

	for (; ColStart != ColEnd; )
	{
		(*ColStart)->ColRelease();

		if (true == (*ColStart)->IsDeath())
		{
			ColStart = m_ColList.erase(ColStart);
		}
		else {
			++ColStart;
		}
	}
}

void ColMgr::ColGroup::OtherCol(ColGroup * _Other)
{
	// 자기 그룹의 Collision들.
	std::list<SPTR<ComCol>>::iterator itColListStart = m_ColList.begin();
	std::list<SPTR<ComCol>>::iterator itColListEnd = m_ColList.end();

	// 다른 충돌그룹의 iterator을 받을 변수.
	std::list<SPTR<ComCol>>::iterator itOtherColStart;
	std::list<SPTR<ComCol>>::iterator itOtherColEnd;

	for (; itColListStart != itColListEnd; ++itColListStart)
	{
		if ((*itColListStart)->IsUpdate() == false)
		{
			continue;
		}
		itOtherColStart = _Other->m_ColList.begin();
		itOtherColEnd = _Other->m_ColList.end();

		for (; itOtherColStart != itOtherColEnd; ++itOtherColStart)
		{
			if ((*itColListStart)->IsUpdate() == false)
			{
				break;
			}
			if ((*itOtherColStart)->IsUpdate() == false)
			{
				continue;
			}
			(*itColListStart)->Col((*itOtherColStart).Get());
		}

	}

}

void ColMgr::ColGroup::ThisCol()
{
}

void ColMgr::ColGroup::ColDataUpdate()
{
	std::list<SPTR<ComCol>>::iterator ColStart = m_ColList.begin();
	std::list<SPTR<ComCol>>::iterator ColEnd = m_ColList.end();

	for (; ColStart != ColEnd; ++ColStart)
	{
		if (false == (*ColStart)->IsUpdate())
		{
			continue;
		}
		(*ColStart)->SubTransUpdate();
		(*ColStart)->ColDataUpdate();
	}
}

void ColMgr::ColGroup::DebugRender()
{
	std::list<SPTR<ComCol>>::iterator ColStart = m_ColList.begin();
	std::list<SPTR<ComCol>>::iterator ColEnd = m_ColList.end();

	for (; ColStart != ColEnd; ++ColStart)
	{
		if ((*ColStart)->IsUpdate())
		{
			(*ColStart)->DebugRender();
		}
	}
}