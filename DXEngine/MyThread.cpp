#include "MyThread.h"
#include "STLHelper.h"

std::unordered_map<std::wstring, SPTR<MyThread>> MyThread::m_ThreadMap;

unsigned int __stdcall ThreadBaseFunc(void * _Arg)
{
	if (nullptr == _Arg)
	{
		assert(false && L"NewThread is Run");
		return 0;
	}

	MyThread* Ptr = (MyThread*)_Arg;

	if (nullptr != Ptr->m_GlobalWork)
	{
		Ptr->m_GlobalWork(Ptr->m_Arg);
	}
	else
	{
		Ptr->m_MemberWork(Ptr->m_Arg);
	}

	Ptr->m_ThreadHandle = nullptr;
	Ptr->m_MemberWork = nullptr;
	Ptr->m_GlobalWork = nullptr;
	Ptr->m_Arg = nullptr;
	return 0;
}


SPTR<MyThread> MyThread::FindThread(const wchar_t * _Name)
{
	return MapFindHelper<SPTR<MyThread>>(m_ThreadMap, _Name);
}

void MyThread::CreateThread(const wchar_t * _Name, _beginthreadex_proc_type _Work, void * _Arg)
{
	SPTR<MyThread> NewThread = FindThread(_Name);

	if (nullptr != NewThread)
	{
		assert(false && L"Fail CreateThread");
		return;
	}

	NewThread = new MyThread();
	m_ThreadMap.insert(std::unordered_map<std::wstring, SPTR<MyThread>>::value_type(_Name, NewThread));

	if (nullptr != _Work)
	{
		NewThread->m_Arg = _Arg;
		NewThread->m_GlobalWork = _Work;
		NewThread->Work();
	}

	return;
}

void MyThread::Work(const wchar_t * _Name, _beginthreadex_proc_type _Work, void * _Arg)
{
	SPTR<MyThread> NewThread = FindThread(_Name);

	if (nullptr != NewThread)
	{
		assert(false && L"NewThread is null");
		return;
	}

	if (true == NewThread->IsWork())
	{
		assert(false && L"NewThread is Run");
		return;
	}

	if (nullptr != _Work)
	{
		NewThread->m_Arg = _Arg;
		NewThread->Work();
	}
}

void MyThread::Work()
{
	m_ThreadHandle = (HANDLE)_beginthreadex(nullptr, 0, ThreadBaseFunc, this, 0, &Id);
}

MyThread::MyThread() : m_ThreadHandle(nullptr), m_MemberWork(nullptr), m_GlobalWork(nullptr), m_Arg(nullptr)
{
}


MyThread::~MyThread()
{
	TerminateThread(m_ThreadHandle, 0);
}
