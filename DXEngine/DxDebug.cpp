#include "DxDebug.h"
#include"DxDevice.h"
#include"VertexShader.h"
#include"PixelShader.h"
#include"Mesh.h"
#include"Level.h"
#include"Camera.h"

void DxDebug::DrawStr(const wchar_t * str, float size, Vector2i pos, Color4f color, FW1_TEXT_FLAG flag)
{
	SPTR<DXFont> Ptr = ResMgr<DXFont>::Find(L"±Ã¼­");
	Ptr->DrawStr(str, size, pos, color, flag);
}

void DxDebug::DrawRect(Vector3f _Pos, const Vector3f & _Scale, const Color4f & _Color, const float _Angle)
{
	SPTR<VertexShader> VTX = ResMgr<VertexShader>::Find(L"VSDebugRect");
	SPTR<PixelShader> PIX = ResMgr<PixelShader>::Find(L"PSDebugRect");
	SPTR<Mesh> MESH = ResMgr<Mesh>::Find(L"DEBUGMESH");

	Matrix4x4 m_MScale;
	Matrix4x4 m_MRot;
	Matrix4x4 m_MPos;
	Matrix4x4 m_W;

	_Pos.z = Level::GetCurLevel()->GetMainCamera()->GetActor()->GetTransform()->GetLocalPosition().z + 1.0f;
	m_MScale.SetScale(_Scale);
	m_MRot.SetRotationDegree(Vector3f(0.0f,0.0f,_Angle));
	m_MPos.SetPosition(_Pos);

	m_W = m_MScale * m_MRot * m_MPos;

	VTX->UpdateCBuffer<Matrix4x4>(0, (m_W * Level::GetCurLevel()->GetMainCamera()->GetMatrixVP()).ReturnTransPose());
	PIX->UpdateCBuffer<Color4f>(0, _Color);

	MESH->Update();
	VTX->Update();
	PIX->Update();

	MESH->Render();
}

DxDebug::DxDebug()
{
}


DxDebug::~DxDebug()
{
}
