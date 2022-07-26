#pragma once
#include "IComponent.h"
#include"Actor.h"
#include"VectorData.h"
class Component : public IComponent
{
public:
	friend class Actor;

private:
	Transform * m_Trans;

public:
	Transform* GetTransform()const;

private:
	static bool IsMultiCheck(Actor* _Actor);
public:
	virtual bool IsUpdate() const override;
	virtual bool IsDeath() const override;

public:
	template<typename T>
	SPTR<T> AddComponent()
	{
		return GetActor()->AddComponent<T>();
	}

	template<typename T, typename InitType>
	SPTR<T> AddComponent(const InitType& _Data)
	{
		return GetActor()->AddComponent<T, InitType>(_Data);
	}
	template<typename T>
	SPTR<T> GetComponent()
	{
		return GetActor()->GetComponent<T>();
	}
protected:
	Component() : m_Trans(nullptr) {}
	virtual ~Component() = 0 {};
};

