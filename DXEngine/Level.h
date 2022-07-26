#pragma once
#include "ILevel.h"
#include"IRefCount.h"
#include"RenderMgr.h"
#include"ColMgr.h"
#include<map>

class Actor;
class Level : public ILevel
{

private:
	static SPTR<Level> m_CurLevel; // 현재 무슨 레벨인지.
	static SPTR<Level> m_NextLevel; // 변경될 다음 레벨.
	static bool m_bDebug;
public:
	static SPTR<Level> CreateLevel(const wchar_t* levelName);

	template<typename T, typename KEYTYPE>
	static SPTR<Level> CreateLevel(KEYTYPE& levelKey)
	{
		SPTR<Level> ptr = CreateLevel(levelKey);

		if (ptr == nullptr)
		{
			assert(false && L"CreateLevel is nullptr");
		}

		ptr->CreateScript<T>();
		return ptr;
	}
	static SPTR<Level> FindLevel(const wchar_t* _Name);

	static bool ChangeLevel(const wchar_t* _Name);
	static SPTR<Level> GetCurLevel()
	{
		return m_CurLevel;
	}
private:
	static void LevelChangeCheck();
public:
	static void LevelUpdate();
	static void LevelRender();

public: 
	bool IsLoading() {
		return isLoading;
	}
	void Loading();

public:
	DEFCREATOR(Level, std::wstring)
		DEFCREATORFUNC()
		DEFCREATORFUNCPARA()
		DEFCREATOREND


public:
	bool Create();
	void Start();
	void End();
	void ScriptUpdate();
	void ScriptLateUpdate();
	void Release();

private:
	std::map<int, std::list<SPTR<Actor>>> m_ActorMap;
	std::map<int, std::list<SPTR<Actor>>>::iterator it_ActorMapStart;
	std::map<int, std::list<SPTR<Actor>>>::iterator it_ActorMapEnd;
	std::list<SPTR<Actor>>::iterator it_ListStart;
	std::list<SPTR<Actor>>::iterator it_ListEnd;
/////////////////////////////////////////////////////////////////////
// Actor
public:
	SPTR<Actor> CreateActor(const wchar_t* _Name = L"GameObject", int _Order = 0);
	SPTR<Actor> CreateActor(int _Order, const wchar_t* _Name = L"GameObject");

	SPTR<Actor> CreateNoneTransformActor(const wchar_t* _Name = L"GameObject", int _Order = 0);
	SPTR<Actor> CreateNoneTransformActor(int _Order, const wchar_t* _Name = L"GameObject");

	bool IsHasActor(const Actor * const actor);
	bool IsHasActor(const Actor * const actor,const int Order);
	SPTR<Actor> FindActor(const wchar_t* actorName);
public:
	void Progress();
	void ActorUpdate();

	void AFixUpdate();
	void AUpdate();
	void ALateUpdate();
	void AEndUpdate();
	void AFinalUpdate();
	void ADebugRender();

/////////////////////////////////
public:
	
	template<typename T>
	SPTR<T> CreateScript()
	{
		T* newUpdater = new T();
		m_ScriptList.push_back(newUpdater);
		newUpdater->SetLevel(this);
		newUpdater->Init();
		return newUpdater;
	}


/////////////////////////////////
private:
	friend class Camera;
	Camera* m_MainCamera;
private:
	void SetMainCamera(Camera* _MainCamera)
	{
		m_MainCamera = _MainCamera;
	}
public:
	Camera* GetMainCamera()const
	{
		return m_MainCamera;
	}
public:
	RenderMgr RMgr;
private:
	void Render();
	///////////////////////////////////////////////////////////
public:
	ColMgr CMgr;
private:
	void Col();
private:
	Level();
	~Level();
	//////////////////////////////////////////////////////////
private:
	struct OverActorInfo : public IRefCount
	{
		std::list<std::wstring> m_OverLevelList;
		SPTR<Actor> m_Actor;

		bool IsOverActor(const wchar_t* _Name);
	};
private:
	static std::list<SPTR<OverActorInfo>> m_OverActor;
	static std::list<SPTR<OverActorInfo>> m_WatingActor;

public:
	void OverActorPush(Actor* actor, std::list<std::wstring> levelList);
	void OverActorProcess();
	static void OverActorChangeCheck();
	static std::list<std::wstring> OverList(Actor* _Actor);
	

};

