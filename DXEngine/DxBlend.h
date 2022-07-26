#pragma once
#include"Resource.h"
#include<d3d11.h>
#include"VectorData.h"
class DxBlend : public Resource
{
public:
	DEFCREATOR(DxBlend, std::wstring)
		DEFCREATORFUNC()
		DEFCREATORFUNCPARA()
		DEFCREATOREND
private:
	ID3D11BlendState* m_Blend;
	Vector4f m_CustomColor;
	unsigned int SmpleMask;
public:
	bool Create();
	void Update();
public:
	DxBlend();
	~DxBlend();
};

