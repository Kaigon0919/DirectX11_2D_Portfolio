#pragma once
#include "Shader.h"
class VertexShader : public Shader
{
public:
	VertexShader();
	~VertexShader();

public:
	DEFLOADER(VertexShader, std::wstring)
	DEFKEYLOADERFUNC(UINT vh, UINT vl, const char* funcName)
	DEFKEYLOADERFUNCPARA(vh,vl,funcName)
	DEFLOADEREND
private:
	ID3D11VertexShader * m_VertexShader;
public:

	bool Load(UINT vh, UINT vl, const char* funcName);
	void Update() override;

public:
	template<class T>
	void UpdateCBuffer(const int key, const T& value)
	{
		SPTR<DXCBuffer> finder = FindCBuffer(key);

		if (nullptr == finder)
		{
			assert(false && L"UpdateCB false");
			return;
		}
		if (finder->TypeCheck<T>() == false)
		{
			assert(false && L"Error CBuffer Type");
			return;
		}

		finder->Update<T>(value);
		finder->VSSet();
		return;
	}
};

