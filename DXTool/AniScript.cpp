#include "stdafx.h"
#include<Level.h>
#include "AniScript.h"
#include<Com2DFrameAni.h>
#include<DxDebug.h>


void AniScript::ChangeAni(const wchar_t * AniName)
{
	Parts->ChangeAni(AniName);
}

void AniScript::CreateAni(const wchar_t * _AniName, unsigned int _StartFrame, unsigned int _EndFrame, float _FrameTime, bool _bLoop)
{
	if (_StartFrame > _EndFrame)
	{
		AfxMessageBox(L"StartFrame이 EndFrame보다 클수 없습니다.");
		return;
	}
	Parts->CreateAni(_AniName, _StartFrame, _EndFrame, _FrameTime, _bLoop);
}

void AniScript::CreateAni(const wchar_t * _AniName, unsigned int _StartFrame, unsigned int _EndFrame, bool _bLoop, float _FrameTime)
{
	if (_StartFrame > _EndFrame)
	{
		AfxMessageBox(L"StartFrame이 EndFrame보다 클수 없습니다.");
		return;
	}
	Parts->CreateAni(_AniName, _StartFrame, _EndFrame, _bLoop, _FrameTime);
}

void AniScript::DeleteAni(const wchar_t * _AniName)
{
	Parts->DeleteAni(_AniName);
}

void AniScript::Clear()
{
	Parts->AniClear();
}

SPTR<Com2DFrameAni> AniScript::GetComFrameAni()
{
	return Parts->GetComFrameAni();
}

void AniScript::SpriteSet(const wchar_t * FileName)
{
	m_SpriteName = FileName;
	Parts->SetSprite(RenderParts::RP_Skin,FileName);
}

void AniScript::SubDataSet(const wchar_t * FileName)
{
	m_SubDataName = FileName;
	Parts->LoadSubData(RenderParts::RP_Skin,FileName);
}


void AniScript::EventDelete(const wchar_t * AniName, unsigned int _StartFrame, unsigned int _EndFrame)
{
	int idx = Parts->FindEventIndex(AniName, _StartFrame, _EndFrame);
	Parts->EventDelete(AniName, idx);
	Parts->EventDelete(AniName, idx);
}
void AniScript::SetPivot(int x, int y)
{
	Parts->SetPivot(Vector2i((int)x, (int)y));
}
bool AniScript::Init()
{
	GetTransform()->SetLocalPosition(Vector3f(0.0f, 0.0f, 0.0f));
	GetTransform()->SetWorldScale(Vector3f(1.0f, 1.0f, 1.0f));\

		SPTR<Actor> PartActor = GetActor()->GetLevel()->CreateActor(GetActor()->GetOrder(), L"RednerParts");
		PartActor->SetParent(GetActor());
		PartActor->GetTransform()->SetWorldScale(Vector3f(1.0f, 1.0f, 1.0f));
		Parts = PartActor->AddComponent<RenderParts>();
	return true;
}

void AniScript::Update()
{
}

void AniScript::LateUpdate()
{
	
}

void AniScript::DebugRender()
{
	if (m_bShowAxis)
	{
		DxDebug::DrawRect(GetTransform()->GetWorldPosition(), Vector3f(100.0f, 1.0f, 1.0f), Color4f(1.0f, 0.0f, 0.0f), GetTransform()->GetWorldRotate().z);
		DxDebug::DrawRect(GetTransform()->GetWorldPosition(), Vector3f(1.0f, 100.0f, 1.0f), Color4f(0.0f, 1.0f, 0.0f), GetTransform()->GetWorldRotate().z);
	}
}

AniScript::AniScript() : m_bShowAxis(false)
{
}


AniScript::~AniScript()
{
}
