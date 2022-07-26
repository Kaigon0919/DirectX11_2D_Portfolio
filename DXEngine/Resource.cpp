#include "Resource.h"



Resource::Resource()
{
}


Resource::~Resource()
{
}

std::wstring Resource::GetPath() const
{
	return m_Path;
}

void Resource::SetPath(const wchar_t * path)
{
	m_Path = path;

	wchar_t ArrDrive[256];
	wchar_t ArrFolder[256];
	wchar_t ArrFile[256];
	wchar_t ArrExt[256];

	_wsplitpath_s(m_Path.c_str(), ArrDrive, ArrFolder, ArrFile, ArrExt);
	Drive = ArrDrive;
	Folder = ArrFolder;
	File = ArrFile;
	Ext = ArrExt;

}

std::wstring Resource::GetFullFileName()
{
	std::wstring output = File + Ext;
	return output;
}

std::wstring Resource::GetFileName()
{
	return File;
}

std::wstring Resource::GetExt()
{
	return Ext;
}

bool Resource::IsExt(const wchar_t * _Name)
{
	return Ext == _Name;
}
