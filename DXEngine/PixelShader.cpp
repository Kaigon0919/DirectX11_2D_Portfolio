#include "PixelShader.h"
#include"UtillMacor.h"
#include"DxDevice.h"
#include"MainWindow.h"



PixelShader::PixelShader() :Shader(SHADERTYPE::SHADERTYPE_PIXEL), m_PixelShader(nullptr)
{
}


PixelShader::~PixelShader()
{
	SAFE_RELEASE(m_PixelShader);
}

bool PixelShader::Load(UINT vh, UINT vl, const char * funcName)
{
	m_VH = vh;
	m_VL = vl;

	UINT iFlag = 0;
#ifdef _DEBUG
	iFlag = D3DCOMPILE_DEBUG;
#endif

	char szBuffer[256] = {};
	wsprintfA(szBuffer, "ps_%d_%d", m_VH, m_VL);

	if (S_OK != D3DCompileFromFile(GetPath().c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, funcName, szBuffer, iFlag, 0, &m_ShaderBlob, &m_ErrBlob))
	{
		std::string ErrorText = (char*)m_ErrBlob->GetBufferPointer();
		MessageBoxA(MainWindow::GetHWND(), ErrorText.c_str(), "PTX Shader Error", MB_OK);
		assert(false);
		return false;
	}
	if (S_OK != DxDevice::GetDevice()->CreatePixelShader(m_ShaderBlob->GetBufferPointer(), m_ShaderBlob->GetBufferSize(), nullptr, &m_PixelShader))
	{
		assert(false);
		return false;
	}
	return true;
}

void PixelShader::Update()
{
	Shader::Update();
	DxDevice::GetContext()->PSSetShader(m_PixelShader, 0, 0);
}
