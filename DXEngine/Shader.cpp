#include "Shader.h"
#include"UtillMacor.h"
#include"DxDevice.h"

Shader::Shader(SHADERTYPE type) : m_Type(type)
{

}


Shader::~Shader()
{
	SAFE_RELEASE(m_ShaderBlob);
	SAFE_RELEASE(m_ErrBlob);
}

void Shader::Update()
{
	if (nullptr != m_Layout)
	{
		m_Layout->Update();
	}
}

void Shader::AddLayout(const char * simenticName, UINT semanticIndex, DXGI_FORMAT format, UINT inputSlot, UINT instanceDataStepRate, D3D11_INPUT_CLASSIFICATION inputSlotClass)
{

	if (nullptr == m_Layout)
	{
		m_Layout = new InputLayout(this);
	}

	m_Layout->AddLayOut(simenticName, semanticIndex, format, inputSlot, instanceDataStepRate, inputSlotClass);
}

void Shader::LayoutCreate()
{
	if (nullptr == m_Layout)
	{
		m_Layout = new InputLayout(this);
	}
	m_Layout->CreateLayout();
}






///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// InputLayout
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Shader::InputLayout::AddLayOut(const char * simenticName, UINT semanticIndex, DXGI_FORMAT format, UINT inputSlot, UINT instanceDataStepRate, D3D11_INPUT_CLASSIFICATION inputSlotClass)
{
	D3D11_INPUT_ELEMENT_DESC InputLayout;
	InputLayout.SemanticName = simenticName;
	InputLayout.SemanticIndex = semanticIndex;
	InputLayout.Format = format;
	InputLayout.InputSlot = inputSlot;
	InputLayout.InputSlotClass = inputSlotClass;
	InputLayout.InstanceDataStepRate = instanceDataStepRate;
	InputLayout.AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
	m_InputLayout.push_back(InputLayout);
}

void Shader::InputLayout::CreateLayout()
{
	if (S_OK != DxDevice::GetDevice()->CreateInputLayout(&m_InputLayout[0], (UINT)m_InputLayout.size(), m_Shader->GetBlob()->GetBufferPointer(), m_Shader->GetBlob()->GetBufferSize(), &m_Layout))
	{
		assert(false);
		return;
	}
}

void Shader::InputLayout::Update()
{
	DxDevice::GetContext()->IASetInputLayout(m_Layout);
}

Shader::InputLayout::InputLayout(Shader * shader) : m_Shader(shader), m_Layout(nullptr)
{
}

Shader::InputLayout::~InputLayout()
{
	SAFE_RELEASE(m_Layout);
}
