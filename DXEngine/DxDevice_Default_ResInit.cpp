#include"DxDevice.h"
#include"PathManager.h"
#include"VertexData.h"
#include"RenderData.h"
#include"VertexShader.h"
#include"PixelShader.h"
#include"Mesh.h"
#include"ResMgr.h"
#include"DxSampler.h"
#include"DxBlend.h"
#include"DXFont.h"

void DxDevice::Default_ResInit()
{
	CreateRSState(L"SOLID", D3D11_CULL_NONE);
	CreateRSState(L"WIRE", D3D11_CULL_NONE, D3D11_FILL_WIREFRAME);
	ChangeRSState(L"SOLID");

	ResMgr<DXFont>::Create(L"궁서");
	ResMgr<DxSampler>::Create(L"DEFSMP");
	ResMgr<DxBlend>::Create(L"DEFBLEND");

	// 사각
	TexVertexData m_ArrTexVertex[4] = {};
	m_ArrTexVertex[0].Position = Vector4f(-0.5f, 0.5f, 0.0f, 1.0f); // 왼쪽위
	m_ArrTexVertex[1].Position = Vector4f(0.5f, 0.5f, 0.0f, 1.0f); // 오른쪽위
	m_ArrTexVertex[2].Position = Vector4f(-0.5f, -0.5f, 0.0f, 1.0f); // 왼쪽 아래
	m_ArrTexVertex[3].Position = Vector4f(0.5f, -0.5f, 0.0f, 1.0f); // 오른쪽 아래

	m_ArrTexVertex[0].TexUV = Vector2f(0.0f, 0.0f); // 왼쪽위
	m_ArrTexVertex[1].TexUV = Vector2f(1.0f, 0.0f); // 오른쪽위
	m_ArrTexVertex[2].TexUV = Vector2f(0.0f, 1.0f); // 왼쪽 아래
	m_ArrTexVertex[3].TexUV = Vector2f(1.0f, 1.0f); // 오른쪽 아래

	IDX32 m_ArrIdx[2] = {};
	m_ArrIdx[0] = IDX32(0, 1, 3);
	m_ArrIdx[1] = IDX32(0, 3, 2);

	UINT vertexSize = sizeof(TexVertexData);
	UINT vertexCount = sizeof(m_ArrTexVertex) / sizeof(TexVertexData);
	UINT indexCount = sizeof(m_ArrTexVertex) / sizeof(DWORD);
	UINT indexSize = IDX32::MemSize();

	ResMgr<Mesh>::Create(L"TEXMESH", m_ArrTexVertex, vertexCount, vertexSize, D3D11_USAGE_DYNAMIC, m_ArrIdx, indexCount, indexSize, D3D11_USAGE_DYNAMIC, DXGI_FORMAT_R32_UINT);

	SPTR<VertexShader> vsPtr = ResMgr<VertexShader>::Load(L"VSTexRect", PathManager::FindPath(L"Shader") + L"TexRect.fx", 5, 0, "VS_Tex");
	vsPtr->AddLayout("POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0);
	vsPtr->AddLayout("TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 0);
	vsPtr->LayoutCreate();


	vsPtr->CreateCBuffer<Matrix4x4>(0, 0, D3D11_USAGE::D3D11_USAGE_DYNAMIC);
	vsPtr->CreateCBuffer<FRect>(1, 1, D3D11_USAGE::D3D11_USAGE_DYNAMIC);

	SPTR<PixelShader> psPtr = ResMgr<PixelShader>::Load(L"PSTexRect", PathManager::FindPath(L"Shader") + L"TexRect.fx", 5, 0, "PS_Tex");
	psPtr->CreateCBuffer<Color4f>(0, 0, D3D11_USAGE::D3D11_USAGE_DYNAMIC);
	psPtr->CreateCBuffer<TexRenderOption>(1, 1, D3D11_USAGE_DYNAMIC);

	// Debug Rect.
	VertexData m_ArrDebugVertex[4] = {};
	m_ArrDebugVertex[0].Position = Vector4f(-0.5f, 0.5f, 0.0f, 1.0f);  // 왼쪽위
	m_ArrDebugVertex[1].Position = Vector4f(0.5f, 0.5f, 0.0f, 1.0f);   // 오른쪽위
	m_ArrDebugVertex[2].Position = Vector4f(0.5f, -0.5f, 0.0f, 1.0f);  // 오른쪽 아래
	m_ArrDebugVertex[3].Position = Vector4f(-0.5f, -0.5f, 0.0f, 1.0f); // 왼쪽 아래

	m_ArrDebugVertex[0].Color = Vector4f(1.0f, 1.0f, 1.0f, 1.0f);
	m_ArrDebugVertex[1].Color = Vector4f(1.0f, 1.0f, 1.0f, 1.0f);
	m_ArrDebugVertex[2].Color = Vector4f(1.0f, 1.0f, 1.0f, 1.0f);
	m_ArrDebugVertex[3].Color = Vector4f(1.0f, 1.0f, 1.0f, 1.0f);

	DWORD m_ArrDebugIdx[5] = { 0,1,2,3,0 };

	vertexSize = sizeof(VertexData);
	vertexCount = sizeof(m_ArrDebugVertex) / sizeof(VertexData);
	indexCount = sizeof(m_ArrDebugIdx) / sizeof(DWORD);
	indexSize = IDX32::MemSize();

	ResMgr<Mesh>::Create(L"DEBUGMESH", m_ArrDebugVertex, vertexCount, vertexSize, D3D11_USAGE_DYNAMIC, m_ArrDebugIdx, indexCount, indexSize, D3D11_USAGE_DYNAMIC, DXGI_FORMAT_R32_UINT, D3D_PRIMITIVE_TOPOLOGY_LINESTRIP);

	// Fill Rect.
	VertexData m_FillVertex[4] = {};
	m_FillVertex[0].Position = Vector4f(-0.5f, 0.5f, 0.0f, 1.0f); // 왼쪽위
	m_FillVertex[1].Position = Vector4f(0.5f, 0.5f, 0.0f, 1.0f); // 오른쪽위
	m_FillVertex[2].Position = Vector4f(-0.5f, -0.5f, 0.0f, 1.0f); // 왼쪽 아래
	m_FillVertex[3].Position = Vector4f(0.5f, -0.5f, 0.0f, 1.0f); // 오른쪽 아래
	m_FillVertex[0].Color = Vector4f(1.0f, 1.0f, 1.0f, 1.0f);
	m_FillVertex[1].Color = Vector4f(1.0f, 1.0f, 1.0f, 1.0f);
	m_FillVertex[2].Color = Vector4f(1.0f, 1.0f, 1.0f, 1.0f);
	m_FillVertex[3].Color = Vector4f(1.0f, 1.0f, 1.0f, 1.0f);

	IDX32 m_FillRectIdx[2] = {};
	m_FillRectIdx[0] = IDX32(0, 1, 3);
	m_FillRectIdx[1] = IDX32(0, 3, 2);

	vertexSize = sizeof(VertexData);
	vertexCount = sizeof(m_FillVertex) / sizeof(VertexData);
	indexCount = sizeof(m_FillRectIdx) / sizeof(DWORD);
	indexSize = IDX32::MemSize();

	ResMgr<Mesh>::Create(L"FILLMESH", m_FillVertex, vertexCount, vertexSize, D3D11_USAGE_DYNAMIC, m_FillRectIdx, indexCount, indexSize, D3D11_USAGE_DYNAMIC, DXGI_FORMAT_R32_UINT);

	SPTR<VertexShader> vsDebugPtr = ResMgr<VertexShader>::Load(L"VSDebugRect", PathManager::FindPath(L"Shader") + L"DebugRect.fx", 5, 0, "VS_DebugRect");
	vsDebugPtr->AddLayout("POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0);
	vsDebugPtr->AddLayout("COLOR", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 0);
	vsDebugPtr->LayoutCreate();
	vsDebugPtr->CreateCBuffer<Matrix4x4>(0, 0, D3D11_USAGE::D3D11_USAGE_DYNAMIC);

	SPTR<PixelShader> psDebugPtr = ResMgr<PixelShader>::Load(L"PSDebugRect", PathManager::FindPath(L"Shader") + L"DebugRect.fx", 5, 0, "PS_DebugRect");
	psDebugPtr->CreateCBuffer<Color4f>(0, 0, D3D11_USAGE::D3D11_USAGE_DYNAMIC);

	
}

