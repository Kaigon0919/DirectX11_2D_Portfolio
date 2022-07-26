#include "DXFont.h"
#include"DxDevice.h"


bool DXFont::Create()
{
	if (S_OK != FW1CreateFactory(FW1_VERSION, &m_FontFactory))
	{
		assert(false && L"Fail, Font createFactory");
		return false;
	}
	if (S_OK != m_FontFactory->CreateFontWrapper(DxDevice::GetDevice(), GetPath().c_str(), &m_FontWrapper))
	{
		assert(false && L"Fail CreateFontWrapper");
		return false;
	}
	return true;
}

void DXFont::DrawStr(const wchar_t * str, float size, Vector2f pos, Color4f color, FW1_TEXT_FLAG flag)
{
	if (m_FontWrapper == nullptr)
	{
		assert(false && L"FontWrapper is nullptr");
		return;
	}

	// ABGR
	UINT32 uiColor = 0;
	UINT32 Temp = 0;
	for (int i = 3; i >= 0; --i)
	{
		Temp = (int)(color[i] * 255);
		uiColor <<= 8;
		uiColor |= Temp;
	}
	m_FontWrapper->DrawString(DxDevice::GetContext(), str, size, pos.x, pos.y, uiColor, flag /*= FW1_TEXT_FLAG::FW1_TOP*/);

	DxDevice::GetContext()->VSSetShader(nullptr, nullptr, 0);
	DxDevice::GetContext()->HSSetShader(nullptr, nullptr, 0);
	DxDevice::GetContext()->GSSetShader(nullptr, nullptr, 0);
	DxDevice::GetContext()->CSSetShader(nullptr, nullptr, 0);
	DxDevice::GetContext()->DSSetShader(nullptr, nullptr, 0);
	DxDevice::GetContext()->PSSetShader(nullptr, nullptr, 0);
	DxDevice::GetContext()->OMSetDepthStencilState(nullptr, 0);
}

DXFont::DXFont() : m_FontFactory(nullptr), m_FontWrapper(nullptr)
{
}


DXFont::~DXFont()
{
	if (m_FontWrapper)
	{
		m_FontWrapper->Release();
		m_FontWrapper = nullptr;
	}
	if (m_FontFactory)
	{
		m_FontFactory->Release();
		m_FontFactory = nullptr;
	}
}
