#pragma once
#include"Resource.h"
#include<d3d11_2.h>
class DxSampler : public Resource
{
private:
	ID3D11SamplerState* m_State;
public:
	ID3D11SamplerState* GetState()
	{
		return m_State;
	}

public:
	DEFCREATOR(DxSampler, std::wstring)
		DEFCREATORFUNC()
		DEFCREATORFUNCPARA()
		DEFCREATOREND
public:
	bool Create();
	void Update();

public:
	DxSampler();
	~DxSampler();
};

