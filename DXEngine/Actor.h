#pragma once
#include"IActor.h"

#include<assert.h>
#include<list>
#include<set>
class Component;
class Transform;
class Actor final : public IActor
{
public:
	friend class Level;

private:
	Transform * m_Trans;

private:
	std::list<SPTR<Component>> m_ComList;
	std::list<SPTR<Component>>::iterator CStartIter;
	std::list<SPTR<Component>>::iterator CEndIter;
	int m_Order;
private:
	void SetOrder(int order)
	{
		m_Order = order;
	}
	void SetLevel(Level * level);
public:
	int GetOrder()const
	{
		return m_Order;
	}


private: // Update Function.
	virtual void FixUpdate() override;
	virtual void Update()override;
	virtual void LateUpdate()override;
	virtual void EndUpdate()override;
	virtual void FinalUpdate()override;
	virtual void DebugRender()override;


private: // template Function.
	template<typename T>
	T* CreateComponent()
	{
		T* newCom = new T();
		newCom->RTTISetting();
		newCom->SetName(newCom->GetTypeNameW().c_str());
		newCom->SetActor(this);
		return newCom;
	}

public: // template Function.
	template<typename T>
	SPTR<Component> AddComponent()
	{
		T* newCom = CreateComponent<T>();
		if (T::IsMultiCheck(this) == false)
		{
			delete newCom;
			return nullptr;
		}
		if (newCom->Init() == false)
		{
			delete newCom;
			return nullptr;
		}
		m_ComList.push_back(newCom);
		return newCom;
	}
	template<typename T, typename InitData>
	SPTR<Component> AddComponent(const InitData& data)
	{
		T* newCom = CreateComponent<T>();
		if (T::IsMultiCheck(this) == false)
		{
			delete newCom;
			return nullptr;
		}
		if (newCom->Init(data) == false)
		{
			delete newCom;
			return nullptr;
		}
		m_ComList.push_back(newCom);
		return newCom;

	}
	template<typename T>
	SPTR<Component> GetComponent()
	{
		std::list<SPTR<Component>>::iterator itFindStart = m_ComList.begin();
		std::list<SPTR<Component>>::iterator itFindEnd = m_ComList.end();

		for (; itFindStart != itFindEnd; ++itFindStart)
		{
			if ((*itFindStart)->IsTypeEqual<T>())
			{
				return (*itFindStart);
			}
			if ((*itFindStart).IsConvert<T>())
			{
				return (*itFindStart);
			}
		}
		return nullptr;
	}
	template<typename T>
	std::list<SPTR<Component>> GetComponents()
	{
		std::list<SPTR<Component>> returnList;
		for (; itFindStart != itFindEnd; ++itFindStart)
		{
			if ((*itFindStart)->IsTypeEqual<T>()) 
			{
				returnList.push_back((*itFindStart));
			}
		}
		return returnList;
	}

public: // Transform Function.
	void SetTransform(Transform * trans);
	Transform* GetTransform()const;
//Child
private:
	Actor* m_Parent;
	std::list<SPTR<Actor>> m_ChildList;
	std::list<SPTR<Actor>>::iterator it_ChildStart;
	std::list<SPTR<Actor>>::iterator it_ChildEnd;

public:
	Actor* GetParent() { return m_Parent; }
	void SetParent(SPTR<Actor> _Parent);
private:
	void ChildCheckProcess();

public:
	virtual void SetUpdate(bool isUpdate)override;
	virtual void Death()override;

public:
	template<typename T>
	std::list<SPTR<T>> GetChildAllCom()
	{
		std::list<SPTR<T>> ReturnList;

		GetChildAllCom(ReturnList);

		return ReturnList;
	}
private:
	template<typename T>
	void GetChildAllCom(std::list<SPTR<T>>& _List)
	{
		std::list<SPTR<Component>>::iterator FindStartIter = m_ComList.begin();
		std::list<SPTR<Component>>::iterator FindEndIter = m_ComList.end();

		for (; FindStartIter != FindEndIter; ++FindStartIter)
		{
			if ((*FindStartIter).IsConvert<T>())
			{
				_List.push_back((*FindStartIter));
			}
		}

		it_ChildStart = m_ChildList.begin();
		it_ChildEnd = m_ChildList.end();
		for (; it_ChildStart != it_ChildEnd; ++it_ChildStart)
		{
			(*it_ChildStart)->GetChildAllCom(_List);
		}
	}
// OverActor
private:
	bool m_bOver;
public:
	template<typename ... Rest>
	void OverActor(Rest ...Arg)
	{
		if (nullptr != m_Parent)
		{
			// 부모가 있는 자식 엑터면, 일단 오버하지 못하게 막는다. 필요할시 예외 처리 예정.
			assert(false && L"Fail OverActor");
			return;
		}

		OverActor(new std::list<std::wstring>() ,Arg...);
	}
	template<typename ... Rest>
	void OverActor(std::list<std::wstring>* list ,const wchar_t * levelName,Rest ...Arg)
	{
		list->push_back(levelName);
		OverActor(list,Arg...);
	}
	void OverActor(std::list<std::wstring>* list, const wchar_t * levelName);

	bool IsOver()const
	{
		return m_bOver;
	}
public:
	Actor();
	~Actor();
};

