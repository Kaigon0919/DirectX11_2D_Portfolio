#include "RenderFillRect.h"
#include"VertexShader.h"
#include"PixelShader.h"
#include"Mesh.h"
#include"DxBlend.h"
#include"Transform.h"
#include"Level.h"
#include"Camera.h"
bool RenderFillRect::Init(int _order)
{
	if (ComRender::Init(_order) == false)
	{
		return false;
	}
	m_Vertex = ResMgr<VertexShader>::Find(L"VSDebugRect");
	m_Pixel = ResMgr<PixelShader>::Find(L"PSDebugRect");
	m_Mesh = ResMgr<Mesh>::Find(L"FILLMESH");
	m_Blend = ResMgr<DxBlend>::Find(L"DEFBLEND");
	return true;
}

void RenderFillRect::Render(const Matrix4x4 & ref)
{
	SubTransUpdate();

	Matrix4x4 WVP = GetSubWorldMat() * ref;
	WVP.TransPose();

	//// Vertex CBUpdate.
	m_Vertex->UpdateCBuffer<Matrix4x4>(0, WVP);

	//// Pixel CBUpdate.
	Color4f EndColor = FillColor * MulColor;
	m_Pixel->UpdateCBuffer<Color4f>(0, EndColor);

	m_Mesh->Update();
	m_Vertex->Update();
	m_Pixel->Update();
	m_Blend->Update();
	m_Mesh->Render();
}

RenderFillRect::RenderFillRect() : MulColor(1.0f, 1.0f, 1.0f, 1.0f)
{
}


RenderFillRect::~RenderFillRect()
{
}
