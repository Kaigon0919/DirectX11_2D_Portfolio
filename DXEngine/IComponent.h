#pragma once

#include"IRefCount.h"
#include"ITypeInfoBase.h"
#include"IActorBase.h"
#include"IUpdate.h"
#include"IName.h"


class IComponent : public virtual IActorBase, public virtual ITypeInfoBase, public virtual IRefCount, public virtual IUpdate, public virtual IName
{
public:
	IComponent() {}
	virtual ~IComponent() = 0 {}
};