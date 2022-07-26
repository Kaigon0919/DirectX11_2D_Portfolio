#pragma once

#include"Resource.h"
#include"IName.h"
#include"ILevelBase.h"

class ILevel : public virtual Resource, public virtual IName
{
public:
	class LevelScript : public virtual Resource, public virtual ILevelBase
	{
	public:
		virtual bool Init(){return true; }
		virtual bool Loading() { return true; } // 씬이 로딩되지 않았을때 한번만 실행
		virtual void Start() {} // 씬이 체인지 되었을때 한번 실행
		virtual void Update() {} // 모든 액터의 업데이트가 실행되기 전에 한번실행
		virtual void LateUpdate() {} // 모든 액터의 업데이트가 끝나고 한번 실행
		virtual void End() {} // 내가 실행중인데 다른씬으로 변경되었을때 한번 실행
		virtual void DebugRender() {}
	public:
		LevelScript() {}
		~LevelScript() {}
	};

protected:
	bool isLoading;
	std::list<SPTR<LevelScript>> m_ScriptList;
	std::list<SPTR<LevelScript>>::iterator UStartIter;
	std::list<SPTR<LevelScript>>::iterator UEndIter;


public:
	ILevel() : isLoading(false){}
	virtual ~ILevel() = 0 {}
};

