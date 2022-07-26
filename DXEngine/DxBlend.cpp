#include "DxBlend.h"
#include"DxDevice.h"
#include"UtillMacor.h"

bool DxBlend::Create()
{
	D3D11_BLEND_DESC des;
	des.AlphaToCoverageEnable = false;
	des.IndependentBlendEnable = false;
	des.RenderTarget[0].BlendEnable = true;
	des.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	des.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	des.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	des.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	des.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	des.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	des.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;

	if (S_OK != DxDevice::GetDevice()->CreateBlendState(&des, &m_Blend))
	{
		assert(false && L"Fail, Create Blend");
		return false;
	}

	return true;
}

void DxBlend::Update()
{
	DxDevice::GetContext()->OMSetBlendState(m_Blend, m_CustomColor.pf, SmpleMask);
}

DxBlend::DxBlend() : m_Blend(nullptr), m_CustomColor(1.0f, 1.0f, 1.0f, 1.0f) , SmpleMask(-1) // -1 = 0xffffffff
{
}


DxBlend::~DxBlend()
{
	SAFE_RELEASE(m_Blend);
}
