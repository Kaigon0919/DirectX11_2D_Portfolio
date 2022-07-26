#include "Tex.h"
#include"DxDevice.h"
#include"UtillMacor.h"



Tex::Tex() : m_Image()
{
}


Tex::~Tex()
{
	SAFE_RELEASE(m_Tex2D);
	SAFE_RELEASE(m_View);
}


bool Tex::Load()
{
	if (IsExt(L".DDS") || IsExt(L".dds"))
	{
		if (S_OK != DirectX::LoadFromDDSFile(GetPath().c_str(), DirectX::DDS_FLAGS_NONE, nullptr, m_Image))
		{
			assert(false && L"Image Load Fail");
			return false;
		}
	}
	else if (IsExt(L".TGA") || IsExt(L".tga"))
	{
		if (S_OK != DirectX::LoadFromTGAFile(GetPath().c_str(), nullptr, m_Image))
		{
			assert(false && L"Image Load Fail");
			return false;
		}
	}
	else
	{
		if (S_OK != DirectX::LoadFromWICFile(GetPath().c_str(), DirectX::WIC_FLAGS_NONE, nullptr, m_Image))
		{
			std::wstring temp = GetPath();
			assert(false && L"Image Load Fail");
			return false;
		}
	}
	size_t Arr = m_Image.GetImageCount();
	if (S_OK != DirectX::CreateShaderResourceView(DxDevice::GetDevice(), m_Image.GetImages(), m_Image.GetImageCount(), m_Image.GetMetadata(), &m_View))
	{
		assert(false && L"Create ResourceView Fail");
		return false;
	}
	assert(nullptr != m_View && L"ResourceView is nullptr");

	m_View->GetResource((ID3D11Resource**)(&m_Tex2D));

	assert(nullptr != m_View && L"GetResource fail");

	m_ImageSize.x = (int)m_Image.GetMetadata().width;
	m_ImageSize.y = (int)m_Image.GetMetadata().height;

	return true;
}


void Tex::Update()
{
	DxDevice::GetContext()->PSSetShaderResources(0, 1, &m_View);
}