#pragma once
#include<string>

class IName
{
protected:
	std::wstring m_Name;

public:
	inline const wchar_t* GetName()
	{
		return m_Name.c_str();
	}
	inline void SetName(const wchar_t * name)
	{
		m_Name = name;
	}
	inline bool Equal(const wchar_t* _Name)
	{
		return m_Name == _Name;
	}
	inline bool Equal(std::wstring _Name)
	{
		return m_Name == _Name;
	}
public:
	IName()						: m_Name(L"None")	{}
	IName(const wchar_t * name) : m_Name(name)		{}

	virtual ~IName() = 0 {};
};

