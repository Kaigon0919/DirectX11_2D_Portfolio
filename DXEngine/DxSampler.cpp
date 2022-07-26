#include "DxSampler.h"
#include"UtillMacor.h"
#include"DxDevice.h"


bool DxSampler::Create()
{
	D3D11_SAMPLER_DESC samplerDes;
	samplerDes.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
	samplerDes.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDes.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDes.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;

	memcpy_s(samplerDes.BorderColor, sizeof(samplerDes.BorderColor), &Vector4f(1.0f, 0.0f, 0.0f, 1.0f), sizeof(Vector4f));
	samplerDes.ComparisonFunc = D3D11_COMPARISON_NEVER;
	samplerDes.MaxAnisotropy = 0;
	samplerDes.MinLOD = -FLT_MAX;
	samplerDes.MaxLOD = FLT_MAX;
	samplerDes.MipLODBias = 0.0f;

	if (S_OK != DxDevice::GetDevice()->CreateSamplerState(&samplerDes, &m_State))
	{
		assert(false && L"Sampler create fail");
		return false;
	}
	return true;
}

void DxSampler::Update()
{
	DxDevice::GetContext()->PSSetSamplers(0, 1, &m_State);
}

DxSampler::DxSampler() : m_State(false)
{
}


DxSampler::~DxSampler()
{
	SAFE_RELEASE(m_State);
}
