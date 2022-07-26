#pragma once

#include <Windows.h>
#include <typeinfo>
#include"IRefCount.h"
#include"DxDevice.h"
#include"UtillMacor.h"
class DXCBuffer : public IRefCount 
{
public:
	DXCBuffer() {}
	~DXCBuffer(){ SAFE_RELEASE(m_CBuffer); }

private:
	const type_info* m_TypeInfo;
	ID3D11Buffer* m_CBuffer;
	UINT m_RegSlot;

public:
	template<typename T>
	bool Create(UINT regSlot, D3D11_USAGE usage)
	{
		m_RegSlot = regSlot;
		m_TypeInfo = &typeid(T);

		D3D11_BUFFER_DESC m_CBDes = {};


		m_CBDes.ByteWidth = sizeof(T);
		m_CBDes.Usage = usage;
		m_CBDes.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

		if (D3D11_USAGE::D3D11_USAGE_DYNAMIC == m_CBDes.Usage)
		{
			m_CBDes.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		}

		if (S_OK != DxDevice::GetDevice()->CreateBuffer(&m_CBDes, nullptr, &m_CBuffer))
		{
			return false;
		}

		return true;
	}

	template<typename T>
	void Update(const T& value)
	{
		D3D11_MAPPED_SUBRESOURCE mapSub = {};
		DxDevice::GetContext()->Map(m_CBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mapSub);
		memcpy_s(mapSub.pData, sizeof(T), &value, sizeof(T));
		DxDevice::GetContext()->Unmap(m_CBuffer,0);
	}

	template<class T>
	bool TypeCheck()
	{
		return m_TypeInfo == &typeid(T);
	}
public:
	void VSSet();
	void PSSet();

};

