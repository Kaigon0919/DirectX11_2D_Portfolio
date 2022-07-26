#pragma once
#ifdef _WIN64

#ifdef _DEBUG
#pragma comment(lib,"DXEngine64d.lib")
#else
#pragma comment(lib,"DXEngine64.lib")
#endif

#else

#ifdef _DEBUG
#pragma comment(lib,"DXEngine32d.lib")
#else
#pragma comment(lib,"DXEngine32.lib")
#endif
#endif
class MiddleStart
{
public:
	static void Init();
	static void SpriteSetting();
public:
	MiddleStart();
	~MiddleStart();
};

