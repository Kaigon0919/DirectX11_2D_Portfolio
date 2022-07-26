#pragma once

#include"VectorData.h"
#include"IRefCount.h"

#include<unordered_map>
#include <d3d11.h> // 다이렉트11 리소스및 자료형 헤더
#include <d3dcompiler.h> // 쉐이더 컴파일용 헤더
#pragma comment(lib, "d3d11")
#pragma comment(lib, "d3dcompiler")
#pragma comment(lib, "dxguid")
#pragma comment(lib, "dxgi.lib")

class DxDevice
{
public:
	DxDevice();
	virtual ~DxDevice() = 0;
public:
	friend class SystemCore;
	friend class DxDeviceDestroyer;
	friend class Level;

private:
	class DxDeviceDestroyer
	{
	public:
		~DxDeviceDestroyer()
		{
			DxDevice::Release();
		}
	};
	static DxDeviceDestroyer Des;
private:
	static ID3D11Device*				m_Device;
	static ID3D11DeviceContext*			m_Context;

	static IDXGISwapChain*				m_SwapChain;
	static ID3D11RenderTargetView*		m_TagetView;

	static ID3D11DepthStencilView*		m_DepthStancilView; // 랜더링시 깊이값에 대한 View객체.
	static ID3D11DepthStencilState*		m_DepthStencilState;
	static ID3D11Texture2D*				m_DepthStancilBuffer;	 // 깊이값을 저장할 텍스처 객체.
	static UINT m_ML;
	static Color4f m_Color;
	static Vector2i m_ViewPortSize;
	static bool m_vsync_enabled;
public:
	static ID3D11Device*		GetDevice() { return m_Device; }
	static ID3D11DeviceContext*	GetContext() { return m_Context; }

private:
	static bool Init();
	static void Release();
	static void ClearTaget();
	static void Present();
	
	static void StateSetting();
	
	static bool CreateDevice();
	static bool CreateSwapChain();
	static bool CreateDepthStancilView();
	static bool CreateViewPort();

/////////////////////////////////////////////////////////////
// 래스터라이저
private:
	class DxRasterizer : public IRefCount
	{
	public:
		ID3D11RasterizerState* m_Raster;
	public:
		~DxRasterizer();
	};
private:
	static std::unordered_map<std::wstring, SPTR<DxRasterizer>> m_RasterMap;

public:
	static void CreateRSState(const wchar_t* _Name, D3D11_CULL_MODE _Cull = D3D11_CULL_BACK, D3D11_FILL_MODE _Fill = D3D11_FILL_SOLID);
	static void ChangeRSState(const wchar_t * _Name);
private:
	static void Default_ResInit();
};

