#pragma once
#include "IRefCount.h"
#include "StlHelper.h"
#include"PathManager.h"
#include "ResMacro.h"

#include <string>
#include <unordered_map>
#include<assert.h>
#include<Windows.h>

class Tex;
class GameSprite;
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<class Res, class Key = std::wstring>
class ResMgr
{
public:
	ResMgr() {}
	~ResMgr() {}
	

private:
	static std::unordered_map<Key, SPTR<Res>> m_ResMap;

public:
	static SPTR<Res> Find(const Key& key)
	{
		return MapFindHelper<SPTR<Res>>(m_ResMap, key);
	}

	static void TexLoadFileInDir(const wchar_t* _key)
	{
		if (&typeid(Tex) != &typeid(Res))
		{
			assert(false);
			return;
		}
		std::wstring temp = PathManager::FindPath(_key);

		std::list<std::wstring> fileList = PathManager::GetAllFile(temp.c_str());
		std::list<std::wstring> DirList = PathManager::GetAllDir(temp.c_str());

		std::list<std::wstring>::iterator itStart = fileList.begin();
		std::list<std::wstring>::iterator itEnd = fileList.end();
		for (; itStart != itEnd; ++itStart)
		{
			Load((temp + (*itStart)));
		}

		itStart = DirList.begin();
		itEnd = DirList.end();
		for (; itStart != itEnd; ++itStart)
		{
			PathManager::PlusCreatePath(_key, (*itStart).c_str(), (*itStart).c_str());
			TexLoadFileInDir((*itStart).c_str());
		}
	}
	static void SpriteCreate(const wchar_t* _key)
	{
		if (&typeid(GameSprite) != &typeid(Res))
		{
			assert(false);
			return;
		}
		std::wstring temp = PathManager::FindPath(_key);
		std::list<std::wstring> fileList = PathManager::GetAllFile(temp.c_str());
		std::list<std::wstring> DirList = PathManager::GetAllDir(temp.c_str());
		std::list<std::wstring>::iterator itStart = fileList.begin();
		std::list<std::wstring>::iterator itEnd = fileList.end();
		for (; itStart != itEnd; ++itStart)
		{
			Create((*itStart).c_str(), (*itStart).c_str());
		}
		itStart = DirList.begin();
		itEnd = DirList.end();
		for (; itStart != itEnd; ++itStart)
		{
			SpriteCreate((*itStart).c_str());
		}
	}
	static void SoundLoadFileInDir(const wchar_t* _key)
	{
		if (&typeid(MySound) != &typeid(Res))
		{
			assert(false);
			return;
		}
		std::wstring temp = PathManager::FindPath(_key);

		std::list<std::wstring> fileList = PathManager::GetAllFile(temp.c_str());
		std::list<std::wstring> DirList = PathManager::GetAllDir(temp.c_str());

		std::list<std::wstring>::iterator itStart = fileList.begin();
		std::list<std::wstring>::iterator itEnd = fileList.end();
		for (; itStart != itEnd; ++itStart)
		{
			Load((temp + (*itStart)));
		}

		itStart = DirList.begin();
		itEnd = DirList.end();
		for (; itStart != itEnd; ++itStart)
		{
			PathManager::PlusCreatePath(_key, (*itStart).c_str(), (*itStart).c_str());
			SoundLoadFileInDir((*itStart).c_str());
		}
	}
public:
	friend class Res::Loader;
	friend class Res::Creator;
	static typename Res::Loader Load;
	static typename Res::Creator Create;
};



template<typename Res, typename Key>
std::unordered_map<Key, SPTR<Res>> ResMgr<Res, Key>::m_ResMap;

template<typename Res, typename Key>
typename Res::Loader ResMgr<Res, Key>::Load;

template<typename Res, typename Key>
typename Res::Creator ResMgr<Res, Key>::Create;