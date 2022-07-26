#include "VertexShader.h"
#include"UtillMacor.h"
#include"DxDevice.h"
#include"MainWindow.h"

VertexShader::VertexShader() : Shader(SHADERTYPE_VERTEX), m_VertexShader(nullptr)
{
}


VertexShader::~VertexShader()
{
	SAFE_RELEASE(m_VertexShader);
}

bool VertexShader::Load(UINT vh, UINT vl, const char * funcName)
{
	m_VH = vh;
	m_VL = vl;

	UINT iFlag = 0;
#ifdef _DEBUG
	iFlag = D3DCOMPILE_DEBUG;
#endif

	char szBuffer[256] = {};
	wsprintfA(szBuffer, "vs_%d_%d", m_VH, m_VL);

	if (S_OK != D3DCompileFromFile(GetPath().c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, funcName, szBuffer, iFlag, 0, &m_ShaderBlob, &m_ErrBlob))
	{
		std::string ErrorText = (char*)m_ErrBlob->GetBufferPointer();
		MessageBoxA(MainWindow::GetHWND(), ErrorText.c_str(), "VTX Shader Error", MB_OK);
		assert(false);
		return false;
	}
	if (S_OK != DxDevice::GetDevice()->CreateVertexShader(m_ShaderBlob->GetBufferPointer(), m_ShaderBlob->GetBufferSize(), nullptr, &m_VertexShader))
	{
		assert(false);
		return false;
	}

	return true;
}

void VertexShader::Update()
{
	Shader::Update();
	DxDevice::GetContext()->VSSetShader(m_VertexShader, 0, 0);
}
