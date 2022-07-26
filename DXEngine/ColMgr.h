#pragma once

// user header include
#include"IRefCount.h"
#include"ComCol.h"
// base header include
#include<list>
#include<unordered_map>

class ColMgr
{
public:
	friend ComCol;
	friend class Level;
private:
	class ColGroup : public IRefCount
	{
	public:
		std::list<ColGroup*> m_Other;
		std::list<SPTR<ComCol>> m_ColList;
	public:
		void PushCol(ComCol * _Col);
		void Col();
		void Release();

		void OtherCol(ColGroup* _Other);
		void ThisCol();
		void ColDataUpdate();
		void DebugRender();
	public:
		ColGroup() {}
		~ColGroup() {}
	};
private:
	std::unordered_map<std::wstring, SPTR<ColGroup>> m_ColMap;

public:
	void ColLink(const wchar_t* left, const wchar_t* right);

private:
	void PushCol(ComCol* _Col);
	SPTR<ColGroup> CreateGroup(const wchar_t* _Name);

public:
	void Release();
	void Col();
	void DebugRender();
public:
	bool IsHasCol(const ComCol * const comCol);
public:
	ColMgr();
	~ColMgr();
};

