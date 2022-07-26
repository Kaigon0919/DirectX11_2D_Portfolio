#pragma once
#include"Resource.h"
#include"DXCBuffer.h"
#include<d3d11.h>

class Shader : public Resource
{
public:
	enum SHADERTYPE
	{
		SHADERTYPE_VERTEX,
		SHADERTYPE_PIXEL,
		SHADERTYPE_MAX
	};

public:
	Shader(SHADERTYPE type);
	virtual ~Shader();


public:
	class InputLayout : public IRefCount
	{
	private:
		Shader* m_Shader;
		std::vector<D3D11_INPUT_ELEMENT_DESC> m_InputLayout;
		ID3D11InputLayout* m_Layout = nullptr;

	public:
		void AddLayOut(const char * simenticName, UINT semanticIndex, DXGI_FORMAT format, UINT inputSlot, UINT instanceDataStepRate, D3D11_INPUT_CLASSIFICATION inputSlotClass = D3D11_INPUT_PER_VERTEX_DATA);

		void CreateLayout();

		void Update();

	public:
		InputLayout(Shader* shader);
		~InputLayout();

	};

protected:
	SHADERTYPE m_Type;
	ID3DBlob * m_ShaderBlob;
	ID3DBlob * m_ErrBlob;
	UINT m_VH;
	UINT m_VL;
	SPTR<InputLayout> m_Layout;
public:
	inline ID3DBlob* GetBlob()const
	{
		return m_ShaderBlob;
	}

public:
	virtual void Update();

public:
	void AddLayout(const char * simenticName, UINT semanticIndex, DXGI_FORMAT format, UINT inputSlot, UINT instanceDataStepRate, D3D11_INPUT_CLASSIFICATION inputSlotClass = D3D11_INPUT_PER_VERTEX_DATA);
	void LayoutCreate();

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ConstBuffer
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
private:
	std::unordered_map<int, SPTR<DXCBuffer>> m_CBufferMap;

public:
	SPTR<DXCBuffer> FindCBuffer(const int key)
	{
		return MapFindHelper<SPTR<DXCBuffer>>(m_CBufferMap, key);
	}

	template<class T>
	void CreateCBuffer(const int key, UINT regSlot, D3D11_USAGE usage)
	{
		if (nullptr != FindCBuffer(key))
		{
			assert(false);
			return;
		}

		DXCBuffer* newBuffer = new DXCBuffer();
		if (false == newBuffer->Create<T>(regSlot, usage))
		{
			assert(false);
			return;
		}
		m_CBufferMap.insert(std::unordered_map<int, SPTR<DXCBuffer>>::value_type(key, newBuffer));
		return;
	}

};

