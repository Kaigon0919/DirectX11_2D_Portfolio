#include "ITypeInfoBase.h"



ITypeInfoBase::ITypeInfoBase() : m_Info(nullptr)
{
}
void ITypeInfoBase::RTTISetting()
{
	m_Info = &(typeid(*this));
}
