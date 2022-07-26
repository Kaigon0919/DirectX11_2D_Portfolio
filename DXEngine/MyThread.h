#pragma once
#include "IRefCount.h"
#include "IName.h"
#include<assert.h>
#include <process.h>
#include <functional>
#include <Windows.h>
#include<unordered_map>

class MyThread :public IRefCount, public IName
{
private:
	static std::unordered_map<std::wstring, SPTR<MyThread>> m_ThreadMap;
private:
	static SPTR<MyThread> FindThread(const wchar_t * _Name);

public:
	// 전역 함수 쓰레드.
	static void CreateThread(const wchar_t * _Name, _beginthreadex_proc_type _Work = nullptr, void * _Arg = nullptr);

	// 맴버 함수  쓰레드.
	template<typename T>
	static void CreateMemberThread(const wchar_t* _Name, unsigned (T::*_Work)(void*) = nullptr, T* _Obj = nullptr, void * _Arg = nullptr)
	{
		SPTR<MyThread> NewThread = FindThread(_Name);

		if (nullptr != NewThread)
		{
			assert(false && L"Error Thread");
			return;
		}

		NewThread = new MyThread();
		m_ThreadMap.insert(std::unordered_map<std::wstring, SPTR<MyThread>>::value_type(_Name, NewThread));
		if (nullptr != _Work && nullptr != _Obj)
		{
			std::function<unsigned(void*)> pFunc = std::bind(_Work, _Obj, std::placeholders::_1);

			if (nullptr == pFunc)
			{
				return;
			}

			NewThread->m_MemberWork = pFunc;
			NewThread->Work();
		}
	}
public:
	void Work(const wchar_t* _Name, _beginthreadex_proc_type _Work, void* _Arg);

	template<typename T>
	void Work(const wchar_t* _Name, unsigned(T::*_Work)(void*), T* _Obj, void* _Arg)
	{
		SPTR<MyThread> NewThread = FindThread(_Name);

		if (nullptr == NewThread)
		{
			assert(false && L"Error Thread");;
			return;
		}

		if (true == NewThread->IsWork())
		{
			assert(false && L"Error Thread");;
			return;
		}

		if (nullptr != _Work && nullptr != _Obj)
		{
			NewThread->m_MemberWork = std::bind(_Work, _Obj, std::placeholders::_1);

			if (nullptr == NewThread->m_MemberWork)
			{
				return;
			}

			NewThread->m_Arg = _Arg;
			NewThread->Work();
		}
	}


	///////////////////////////////////////// Member
private:
	unsigned int Id;
	void* m_Arg;
	HANDLE m_ThreadHandle;
	std::function<unsigned(void*)> m_MemberWork;
	_beginthreadex_proc_type m_GlobalWork;

	friend unsigned int __stdcall ThreadBaseFunc(void* _Arg);

public:
	bool IsWork()
	{
		return m_ThreadHandle != nullptr;
	}

	void Work();
public:
	MyThread();
	~MyThread();
};

