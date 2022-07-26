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
		virtual bool Loading() { return true; } // ���� �ε����� �ʾ����� �ѹ��� ����
		virtual void Start() {} // ���� ü���� �Ǿ����� �ѹ� ����
		virtual void Update() {} // ��� ������ ������Ʈ�� ����Ǳ� ���� �ѹ�����
		virtual void LateUpdate() {} // ��� ������ ������Ʈ�� ������ �ѹ� ����
		virtual void End() {} // ���� �������ε� �ٸ������� ����Ǿ����� �ѹ� ����
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

