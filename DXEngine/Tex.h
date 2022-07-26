#pragma once
#include"Resource.h"
#include"VectorData.h"
#include<DirectXTex\DirectXTex.h>


#ifdef _WIN64
#ifdef _DEBUG
#pragma comment(lib,"DirectXTex\\DirectXTex64d.lib")
#else
#pragma comment(lib,"DirectXTex\\DirectXTex64.lib")
#endif
#else
#ifdef _DEBUG
#pragma comment(lib,"DirectXTex\\DirectXTex32d.lib")
#else
#pragma comment(lib,"DirectXTex\\DirectXTex32.lib")
#endif
#endif


class Tex: public Resource
{
private:
	DirectX::ScratchImage m_Image;
	ID3D11Texture2D*      m_Tex2D;
	Vector2i m_ImageSize;

	ID3D11ShaderResourceView* m_View;

public:
	DEFLOADER(Tex, std::wstring)
		DEFPATHLOADERFUNC()
		DEFPATHLOADERFUNCPARA()
		DEFLOADEREND
public:
	bool Load();
	void Update();
public:
	Vector2i GetImageSize()const
	{
		return m_ImageSize;
	}
public:
	Tex();
	~Tex();
};

