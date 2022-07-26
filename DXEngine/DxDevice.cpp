#include "DxDevice.h"
#include"MainWindow.h"
#include"UtillMacor.h"
#include"STLHelper.h"
#include <DirectXPackedVector.h> 

DxDevice::DxDeviceDestroyer DxDevice::Des;

Color4f DxDevice::m_Color = { 0.0f, 0.5f, 0.5f, 1.0f };

ID3D11Device*				DxDevice::m_Device				= nullptr;
ID3D11DeviceContext*		DxDevice::m_Context				= nullptr;
IDXGISwapChain*				DxDevice::m_SwapChain			= nullptr;
ID3D11RenderTargetView*		DxDevice::m_TagetView			= nullptr;
ID3D11DepthStencilView*		DxDevice::m_DepthStancilView	= nullptr;
ID3D11Texture2D*			DxDevice::m_DepthStancilBuffer	= nullptr;
ID3D11DepthStencilState*	DxDevice::m_DepthStencilState	= nullptr;
UINT						DxDevice::m_ML = 0;
bool						DxDevice::m_vsync_enabled = true;
DxDevice::DxDevice()
{
}


DxDevice::~DxDevice()
{
}

bool DxDevice::Init()
{
	if (false == CreateDevice())
	{
		Release();
		return false;
	}

	if (false == CreateSwapChain())
	{
		Release();
		return false;
	}

	if (false == CreateDepthStancilView())
	{
		Release();
		return false;
	}

	if (false == CreateViewPort())
	{
		Release();
		return false;
	}

	Default_ResInit();



	return true;
}

void DxDevice::Release()
{
	if (m_DepthStencilState)
	{
		m_DepthStencilState->Release();
		m_DepthStencilState = nullptr;
	}
	if(m_DepthStancilBuffer)
	{ 
		m_DepthStancilBuffer->Release();
		m_DepthStancilBuffer = nullptr;
	}
	if (m_DepthStancilView) 
	{ 
		m_DepthStancilView->Release();
		m_DepthStancilView = nullptr;
	}
	if (m_TagetView)		
	{ 
		m_TagetView->Release();
		m_TagetView = nullptr;
	}
	if (m_SwapChain)
	{ 
		m_SwapChain->Release();
		m_SwapChain = nullptr;
	}
	if (m_Context)			
	{ 
		m_Context->Release();
		m_Context = nullptr;
	}
	if (m_Device) 
	{ 
		m_Device->Release(); 
		m_Device = nullptr;
	}
}

void DxDevice::ClearTaget()
{
	m_Context->ClearRenderTargetView(m_TagetView, m_Color.pf);
	m_Context->ClearDepthStencilView(m_DepthStancilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
}

void DxDevice::Present()
{
	if (m_vsync_enabled)
	{
		m_SwapChain->Present(1, 0);
	}
	else
	{
		m_SwapChain->Present(0, 0);
	}
}

void DxDevice::StateSetting()
{
	// Set the depth stencil state.
	m_Context->OMSetDepthStencilState(m_DepthStencilState, 1);
}

bool DxDevice::CreateDevice()
{
	int iFlag = 0;
#ifdef _DEBUG
	iFlag = D3D11_CREATE_DEVICE_DEBUG;
#endif

	D3D_FEATURE_LEVEL featureLevel = D3D_FEATURE_LEVEL::D3D_FEATURE_LEVEL_11_0;

	if (S_OK != D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE::D3D_DRIVER_TYPE_HARDWARE, nullptr, iFlag, nullptr, 0, D3D11_SDK_VERSION, &m_Device, &featureLevel, &m_Context))
	{
		return false;
	}
	m_Device->CheckMultisampleQualityLevels(DXGI_FORMAT_R8G8B8A8_UNORM, 4, &m_ML);
	return true;
}

bool DxDevice::CreateSwapChain()
{
	IDXGIFactory* factory = nullptr;;
	IDXGIAdapter* adapter = nullptr;;
	IDXGIOutput* adapterOutput = nullptr;;
	DXGI_MODE_DESC* displayModeList = {};
	UINT numModes = 0;
	UINT numerator, denominator;
	Vector2i winSize = MainWindow::GetSize();

	if (S_OK != CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&factory))
	{
		assert(false);
		return false;
	}

	if (S_OK != factory->EnumAdapters(0, &adapter))
	{
		assert(false);
		return false;
	}
	if (S_OK != adapter->EnumOutputs(0, &adapterOutput))
	{
		assert(false);
		return false;
	}
	if (S_OK != adapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numModes, NULL))
	{
		assert(false);
		return false;
	}
	displayModeList = new DXGI_MODE_DESC[numModes];
	if (!displayModeList)
	{
		assert(false);
		return false;
	}
	if (S_OK != adapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numModes, displayModeList))
	{
		assert(false);
		return false;
	}
	for (UINT i = 0; i < numModes; i++)
	{
		if (displayModeList[i].Width == (unsigned int)winSize.x)
		{
			if (displayModeList[i].Height == (unsigned int)winSize.y)
			{
				numerator = displayModeList[i].RefreshRate.Numerator;
				denominator = displayModeList[i].RefreshRate.Denominator;
			}
		}
	}

	DXGI_SWAP_CHAIN_DESC swapDecs = {};
	swapDecs.BufferDesc.Width = winSize.x;
	swapDecs.BufferDesc.Height = winSize.y;

	if (m_vsync_enabled)
	{
		swapDecs.BufferDesc.RefreshRate.Numerator = numerator;
		swapDecs.BufferDesc.RefreshRate.Denominator = denominator;
	}
	else
	{
		swapDecs.BufferDesc.RefreshRate.Numerator = 0;
		swapDecs.BufferDesc.RefreshRate.Denominator = 1;
	}

	swapDecs.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapDecs.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	swapDecs.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	swapDecs.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapDecs.SampleDesc.Count = 1;
	swapDecs.SampleDesc.Quality = 0;
	swapDecs.OutputWindow = MainWindow::GetHWND();
	swapDecs.BufferCount = 1;
	swapDecs.SwapEffect = DXGI_SWAP_EFFECT::DXGI_SWAP_EFFECT_DISCARD;
	swapDecs.Windowed = !MainWindow::IsFull();
	
	if (S_OK != factory->CreateSwapChain(m_Device, &swapDecs, &m_SwapChain))
	{
		return false;
	}

	if (displayModeList)
	{
		delete[] displayModeList;
		displayModeList = nullptr;
	}
	// 출력 아답터를 할당 해제합니다.
	if (adapterOutput)
	{
		adapterOutput->Release();
		adapterOutput = nullptr;
	}
	// 아답터를 할당 해제합니다.
	if (adapter)
	{
		adapter->Release();
		adapter = nullptr;
	}
	// 팩토리 객체를 할당 해제합니다.
	if (factory)
	{
		factory->Release();
		factory = nullptr;
	}

	return true;
}

bool DxDevice::CreateDepthStancilView()
{
	ID3D11Texture2D* pBackBufferTex = nullptr;
	if (S_OK != m_SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&pBackBufferTex))
	{
		assert(false && L"Fail GetBuffer, CreateDepthStancilView");
		return false;
	}
	if (S_OK != m_Device->CreateRenderTargetView(pBackBufferTex, 0, &m_TagetView))
	{
		assert(false && L"Fail create RTV, CreateDepthStancilView");
		return false;
	}

	if (pBackBufferTex)
	{
		pBackBufferTex->Release();
		pBackBufferTex = nullptr;
	}

	D3D11_TEXTURE2D_DESC depthStancDecs = {};

	depthStancDecs.ArraySize = 1;
	depthStancDecs.Width = (UINT)MainWindow::GetSize().x;
	depthStancDecs.Height = (UINT)MainWindow::GetSize().y;
	depthStancDecs.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStancDecs.SampleDesc.Count = 1;
	depthStancDecs.SampleDesc.Quality = 0;
	depthStancDecs.MipLevels = 1;
	depthStancDecs.Usage = D3D11_USAGE_DEFAULT;
	depthStancDecs.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthStancDecs.CPUAccessFlags = 0;
	depthStancDecs.MiscFlags = 0;

	m_Device->CreateTexture2D(&depthStancDecs, 0, &m_DepthStancilBuffer);
	if (nullptr == m_DepthStancilBuffer)
	{
		assert(false && L"Fail, DepthStecil");
		return false;
	}

	if (S_OK != m_Device->CreateDepthStencilView(m_DepthStancilBuffer, 0, &m_DepthStancilView))
	{
		assert(false && L"Fail, DepthStecil");
		return false;
	}
	m_Context->OMSetRenderTargets(1, &m_TagetView, m_DepthStancilView);

	// depthStencil State.
	D3D11_DEPTH_STENCIL_DESC depthStencilDesc = {};
	depthStencilDesc.DepthEnable = false;
	depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;

	depthStencilDesc.StencilEnable = true;
	depthStencilDesc.StencilReadMask = 0xFF;
	depthStencilDesc.StencilWriteMask = 0xFF;

	// Stencil operations if pixel is front-facing.
	depthStencilDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
	depthStencilDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	// Stencil operations if pixel is back-facing.
	depthStencilDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
	depthStencilDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	// Create the depth stencil state.
	HRESULT result = m_Device->CreateDepthStencilState(&depthStencilDesc, &m_DepthStencilState);
	if (FAILED(result))
	{
		return false;
	}

	// Set the depth stencil state.
	m_Context->OMSetDepthStencilState(m_DepthStencilState, 1);


	return true;
}

bool DxDevice::CreateViewPort()
{
	D3D11_VIEWPORT vpDecs = {};

	vpDecs.TopLeftX = 0;
	vpDecs.TopLeftY = 0;

	vpDecs.Width = (float)MainWindow::GetSize().x;
	vpDecs.Height = (float)MainWindow::GetSize().y;

	vpDecs.MinDepth = 0;
	vpDecs.MaxDepth = 1;

	m_Context->RSSetViewports(1, &vpDecs);
	return true;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// DxRasterizer

std::unordered_map<std::wstring, SPTR<DxDevice::DxRasterizer>> DxDevice::m_RasterMap;

DxDevice::DxRasterizer::~DxRasterizer()
{
	SAFE_RELEASE(m_Raster);
}

void DxDevice::CreateRSState(const wchar_t * _Name, D3D11_CULL_MODE _Cull, D3D11_FILL_MODE _Fill)
{
	if (nullptr != MapFindHelper<SPTR<DxRasterizer>>(m_RasterMap, _Name))
	{
		assert(false && L"the Rasterizer already exists.");
		return;
	}

	SPTR<DxRasterizer> Res = new DxRasterizer();

	D3D11_RASTERIZER_DESC des = {};
	des.CullMode = _Cull;
	des.FillMode = _Fill;
	des.AntialiasedLineEnable = false;
	des.DepthBias = 0;
	des.DepthBiasClamp = 0.0f;
	des.DepthClipEnable = true;
	des.FrontCounterClockwise = false;
	des.MultisampleEnable = false;
	des.ScissorEnable = false;
	des.SlopeScaledDepthBias = 0.0f;
	if (S_OK != m_Device->CreateRasterizerState(&des, &(Res->m_Raster)))
	{
		assert(false && L"Fail, CreateRasterizer");
		return;
	}
	m_RasterMap.insert(std::unordered_map<std::wstring, SPTR<DxRasterizer>>::value_type(_Name, Res));
}

void DxDevice::ChangeRSState(const wchar_t * _Name)
{
	SPTR<DxRasterizer> ptr = MapFindHelper<SPTR<DxRasterizer>>(m_RasterMap, _Name);
	if (ptr == nullptr)
	{
		assert(false && L"fail, did not find Rasterize");
		return;
	}
	m_Context->RSSetState(ptr->m_Raster);
}