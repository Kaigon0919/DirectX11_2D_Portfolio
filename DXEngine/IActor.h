#pragma once
#include "IRefCount.h"
#include "ITypeInfoBase.h"
#include"IUpdate.h"
#include"IName.h"
#include"ILevelBase.h"
class IActor : public virtual ITypeInfoBase,  public virtual IRefCount, public virtual IUpdate, public virtual IName, public ILevelBase
{
private:

public:
	IActor() {}
	virtual ~IActor() = 0 {}
};

