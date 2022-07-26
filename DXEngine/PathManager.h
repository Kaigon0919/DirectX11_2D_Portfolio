#pragma once
#include <unordered_map>
#include <list>
class PathManager
{
private:
	PathManager();
	virtual ~PathManager() = 0;
private:
	static std::unordered_map<std::wstring, std::wstring> m_PathMap;
	static std::wstring m_Root;
	static bool isInit;
private:
	static void Init();
public:
	static std::wstring FindPath(const wchar_t * key);

	static bool RootToCreatePath(const wchar_t * key);
	static bool RootToCreatePath(const wchar_t * key, const wchar_t * foderName);
	static bool PlusCreatePath(const wchar_t* _Base, const wchar_t* _Folder, const wchar_t* _Key);

	static std::wstring PathToFullFileName(const std::wstring& path);
	static std::list<std::wstring> GetAllFile(const wchar_t* _folder);
	static std::list<std::wstring> GetAllDir(const wchar_t* _folder);
	static std::wstring GetRootPath();
};

