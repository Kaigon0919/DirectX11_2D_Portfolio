#pragma once

template<typename classA, typename classB>
class Compile_Dynamic_Cast
{
private:
	static classB* m_CheckPtr;

private:
	static const bool isInheritance;

private:
	static bool Check(...);
	static short Check(classA* p);

public:
	static bool IsRelation()
	{
		return isInheritance;
	}
};

template<typename classA, typename classB>
classB* Compile_Dynamic_Cast<classA, classB>::m_CheckPtr = nullptr;

template<typename classA, typename classB>
const bool Compile_Dynamic_Cast<classA, classB>::isInheritance = sizeof(Check(m_CheckPtr)) - 1;
