#pragma once
#include<typeinfo>
#include <string> 
#include<atlstr.h>


class ITypeInfoBase
{
public:
	ITypeInfoBase();
	virtual ~ITypeInfoBase() = 0 {}

public:
	const type_info* m_Info;

public:
	void RTTISetting();

	template<class T>
	bool IsTypeEqual()
	{
		return m_Info == &typeid(T);
	}
	template<class T>
	bool IsTypeBefore()
	{
		return m_Info->before(typeid(T));
	}
	std::string GetTypeName()const
	{
		return m_Info->name();
	}

	std::wstring GetTypeNameW()const
	{
		std::wstring temp = CA2W(m_Info->name());
		return temp;
	}
};

