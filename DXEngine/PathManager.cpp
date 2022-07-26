#include "PathManager.h"
#include <assert.h>
#include <Windows.h>

std::unordered_map<std::wstring, std::wstring> PathManager::m_PathMap;
std::wstring PathManager::m_Root;
bool PathManager::isInit = false;

PathManager::PathManager()
{
}


PathManager::~PathManager()
{
}

void PathManager::Init()
{
	wchar_t ArrStr[256] = {};
	GetCurrentDirectoryW(sizeof(wchar_t) * 256, ArrStr);
	m_Root = ArrStr;

	size_t CutCount = m_Root.find_last_of(L'\\', m_Root.size());
	m_Root = m_Root.replace(CutCount, m_Root.size(), L"\\Bin\\");

	isInit = true;
}

std::wstring PathManager::FindPath(const wchar_t * key)
{
	if (isInit == false)
	{
		Init();
	}
	std::unordered_map<std::wstring, std::wstring>::iterator FindIter = m_PathMap.find(key);

	if (FindIter != m_PathMap.end())
	{
		return FindIter->second;
	}

	return L"";
}

bool PathManager::RootToCreatePath(const wchar_t * key)
{
	return RootToCreatePath(key, key);
}

bool PathManager::RootToCreatePath(const wchar_t * key, const wchar_t * foderName)
{
	if (isInit == false)
	{
		Init();
	}
	std::unordered_map<std::wstring, std::wstring>::iterator FindIter = m_PathMap.find(key);

	if (FindIter != m_PathMap.end())
	{
		assert(false);
		return false;
	}

	m_PathMap.insert(std::unordered_map<std::wstring, std::wstring>::value_type(key, m_Root + foderName + L"\\"));

	return true;
}
bool PathManager::PlusCreatePath(const wchar_t * _Base, const wchar_t * _Folder, const wchar_t * _Key)
{
	std::unordered_map<std::wstring, std::wstring>::iterator FindIter = m_PathMap.find(_Key);

	if (FindIter != m_PathMap.end())
	{
		assert(false);
		return false;
	}

	FindIter = m_PathMap.find(_Base);

	if (FindIter == m_PathMap.end())
	{
		assert(false);
		return false;
	}

	m_PathMap.insert(std::unordered_map<std::wstring, std::wstring>::value_type(_Key, FindIter->second + _Folder + L"\\"));

	return true;
}
std::wstring PathManager::PathToFullFileName(const std::wstring& path)
{
	if (isInit == false)
	{
		Init();
	}
	wchar_t ArrDrive[256];
	wchar_t ArrFolder[256];
	wchar_t ArrFile[256];
	wchar_t ArrExt[256];

	_wsplitpath_s(path.c_str(), ArrDrive, ArrFolder, ArrFile, ArrExt);

	std::wstring returnValue = ArrFile;
	returnValue += ArrExt;
	return returnValue;
}

std::list<std::wstring> PathManager::GetAllFile(const wchar_t* _folder)
{
	if (isInit == false)
	{
		Init();
	}
	std::list<std::wstring> temp;
	wchar_t search_path[1024] = { 0, };
	wsprintfW(search_path, L"%s/*.*", _folder);

	WIN32_FIND_DATA fd;
	HANDLE hFind = FindFirstFile(search_path, &fd);
	if (hFind != INVALID_HANDLE_VALUE)
	{
		FindNextFile(hFind, &fd);
		while (FindNextFile(hFind, &fd))
		{
			if (lstrcmpW(fd.cFileName,L"desktop.ini") == 0 || fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{
				continue;
			}
			temp.push_back(fd.cFileName);
		} 
		FindClose(hFind);
	}
	return temp;
}

std::list<std::wstring> PathManager::GetAllDir(const wchar_t* _folder)
{
	if (isInit == false)
	{
		Init();
	}
	std::list<std::wstring> temp;
	wchar_t search_path[1024] = { 0, };
	wsprintfW(search_path, L"%s/*.*", _folder);

	WIN32_FIND_DATA fd;
	HANDLE hFind = FindFirstFile(search_path, &fd);
	if (hFind != INVALID_HANDLE_VALUE)
	{
		FindNextFile(hFind, &fd);
		while (FindNextFile(hFind, &fd))
		{
			if (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{
				temp.push_back(fd.cFileName);
			}
		}
		FindClose(hFind);
	}
	return temp;
}

std::wstring PathManager::GetRootPath()
{
	return m_Root;
}