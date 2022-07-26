#pragma once
#include<string>

#include"IRefCount.h"
#include"ITypeInfoBase.h"
#include "ResMgr.h"


class Resource : public virtual IRefCount, public virtual ITypeInfoBase
{
public:
	Resource();
	virtual ~Resource() = 0;
public:
	template<typename Res, typename Key>
	friend class ResMgr;

	class Creator {};
	class Loader {};
private:
	struct 
	{
		std::wstring Drive ;
		std::wstring Folder;
		std::wstring File  ;
		std::wstring Ext   ;
	};

private:
	std::wstring m_Path;
public:
	std::wstring GetPath()const;
	void SetPath(const wchar_t* path);

	std::wstring GetFullFileName();
	std::wstring GetFileName();
	std::wstring GetExt();

public:
	bool IsExt(const wchar_t * _Name);
};

