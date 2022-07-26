#pragma once
#include<SystemCore.h>

#ifdef _WIN64

#ifdef _DEBUG
#pragma comment(lib,"DXMiddle64d.lib")
#else
#pragma comment(lib,"DXMiddle64.lib")
#endif

#else

#ifdef _DEBUG
#pragma comment(lib,"DXMiddle32d.lib")
#else
#pragma comment(lib,"DXMiddle32.lib")
#endif
#endif
class FirstCore : public SystemCore::CoreBuilder
{
public:
	FirstCore();
	~FirstCore();

public:
	virtual bool Build();
};

CORERUN(FirstCore, L"First", Vector2i(1280,720))

