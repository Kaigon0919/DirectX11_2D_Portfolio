#pragma once

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//// Define
////////////////////////
#pragma region CREATORDEF

#define DEFCREATOR(RESTYPE, KEYTYPE) class Creator { public: typedef RESTYPE ResType; typedef KEYTYPE KeyType;

#define DEFCREATORFUNC(...) SPTR<ResType> operator()(const KeyType& key, ##__VA_ARGS__) { ResType* newRes = new ResType(); newRes->SetPath(key.c_str());

#define DEFCREATORFUNCPARA(...) if(false == newRes->Create( ##__VA_ARGS__ )) {	assert(false);	delete newRes;	return nullptr; } ResMgr<ResType, KeyType>::m_ResMap.insert(std::unordered_map<KeyType, SPTR<ResType>>::value_type(key, newRes)); return newRes; }

#define DEFCREATOREND }; friend Creator;

#pragma endregion

#pragma region LOADERDEF
#define DEFLOADER(RESTYPE, KEYTYPE) public: class Loader { public: 	typedef RESTYPE ResType; typedef KEYTYPE KeyType; 

#define DEFKEYLOADERFUNC(...) SPTR<ResType> operator()(const KeyType& _Key, const std::wstring& _Path, __VA_ARGS__) { ResType* NewRes = new ResType(); NewRes->SetPath(_Path.c_str()); 

#define DEFKEYLOADERFUNCPARA(...) if (false == NewRes->Load( ## __VA_ARGS__ ## )) { assert(false); delete NewRes; return nullptr; } ResMgr<ResType, KeyType>::m_ResMap.insert(std::unordered_map<KeyType, SPTR<ResType>>::value_type(_Key, NewRes)); return NewRes; }

#define DEFLOADEREND }; friend Loader;

#pragma endregion

#pragma region PATHLOADERDEF
#define DEFPATHLOADERFUNC(...)\
 SPTR<ResType> operator()(const std::wstring& _path, __VA_ARGS__)\
{\
	SPTR<ResType> FindPtr = ResMgr<ResType,KeyType>::Find(PathManager::PathToFullFileName(_path));\
	 if(nullptr!=FindPtr)\
	{\
		return FindPtr;\
	}\
	ResType* NewRes = new ResType();\
	NewRes->SetPath(_path.c_str());

#define DEFPATHLOADERFUNCPARA(...) if (false == NewRes->Load( ## __VA_ARGS__ ## )) { assert(false); delete NewRes; return nullptr; } ResMgr<ResType, KeyType>::m_ResMap.insert(std::unordered_map<KeyType, SPTR<ResType>>::value_type(NewRes->GetFullFileName(), NewRes)); return NewRes; }

#pragma endregion
