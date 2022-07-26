#pragma once

#include"Resource.h"
#include"VectorData.h"
#include<FW1FontWrapper\FW1FontWrapper.h>


#ifdef _WIN64

#ifdef _DEBUG
#pragma comment(lib,"FW1FontWrapper\\FW1FontWrapper64d.lib")
#else
#pragma comment(lib,"FW1FontWrapper\\FW1FontWrapper64.lib")
#endif

#else
#ifdef _DEBUG
#pragma comment(lib,"FW1FontWrapper\\FW1FontWrapper32d.lib")
#else
#pragma comment(lib,"FW1FontWrapper\\FW1FontWrapper32.lib")
#endif
#endif



class DXFont : public Resource
{
private:
	IFW1Factory * m_FontFactory;
	IFW1FontWrapper * m_FontWrapper;

public:
	DEFCREATOR(DXFont , std::wstring)
		DEFCREATORFUNC()
		DEFCREATORFUNCPARA()
		DEFCREATOREND
public:
	bool Create();
	void DrawStr(const wchar_t * str, float size, Vector2f pos, Color4f color, FW1_TEXT_FLAG flag = FW1_TEXT_FLAG::FW1_TOP);

public:
	DXFont();
	~DXFont();
};

