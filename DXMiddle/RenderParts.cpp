#include "RenderParts.h"


#include<Render2DSprite.h>
#include<Com2DFrameAni.h>
#include<BRStream.h>
#include<DxDebug.h>
#include<Level.h>
bool RenderParts::Init()
{
	m_Trans = GetTransform();
	Pivot.x = 0;
	Pivot.y = 0;

	return true;
}

void RenderParts::FixUpdate()
{

}

void RenderParts::Update()
{
	for (int i = 0; i < RP_Max; ++i)
	{
		PivotUpdate((eRednerParts)i);
	}
}

void RenderParts::LateUpdate()
{

}

void RenderParts::EndUpdate()
{

}

void RenderParts::DebugRender()
{

}
void RenderParts::SetPivot(const Vector2i& pivot)
{
	Pivot = pivot;
}
void RenderParts::SetSprite(eRednerParts PartNumber, const wchar_t * SpriteName)
{
	if (m_Render[PartNumber] == nullptr)
	{
		SPTR<Actor> partActors = GetActor()->GetLevel()->CreateActor(GetActor()->GetOrder(), L"RenderPart");
		partActors->SetParent(GetActor());
		m_Render[PartNumber] = partActors->AddComponent<Render2DSprite>(1);
		m_FrameAni[PartNumber] = partActors->AddComponent<Com2DFrameAni>();
	}
	m_Render[PartNumber]->SetSprite(SpriteName, m_FrameAni[0]->GetCurIndex());
	m_Render[PartNumber]->GetTransform()->SetLocalScale(m_Render[PartNumber]->GetSpriteImageSize(0));
}
void RenderParts::DeletePart(eRednerParts PartNumber)
{
	if (m_Render[PartNumber] != nullptr)
	{
		m_Render[PartNumber]->Death();
		m_Render[PartNumber] = nullptr;
	}
	if (m_FrameAni[PartNumber] != nullptr)
	{
		m_FrameAni[PartNumber]->Death();
		m_FrameAni[PartNumber] = nullptr;
	}
}
void RenderParts::DeleteAllPart()
{
	for (int i = 0; i < RP_Max; ++i)
	{
		DeletePart((eRednerParts)i);
	}
}
void RenderParts::CreateAni(const wchar_t * _AniName, unsigned int _StartFrame, unsigned int _EndFrame, float _FrameTime, bool _bLoop)
{
	for (int i = 0; i < RP_Max; ++i)
	{
		if (m_FrameAni[i] == nullptr)
		{
			continue;
		}
		m_FrameAni[i]->CreateAni(_AniName, _StartFrame, _EndFrame, _FrameTime, _bLoop);
	}
}
void RenderParts::CreateAni(const wchar_t * _AniName, unsigned int _StartFrame, unsigned int _EndFrame, bool _bLoop, float _FrameTime)
{
	for (int i = 0; i < RP_Max; ++i)
	{
		if (m_FrameAni[i] == nullptr)
		{
			continue;
		}
		m_FrameAni[i]->CreateAni(_AniName, _StartFrame, _EndFrame, _bLoop, _FrameTime);
	}
}

void RenderParts::DeleteAni(const wchar_t* _AniName)
{
	for (int i = 0; i < RP_Max; ++i)
	{
		if (m_FrameAni[i] == nullptr)
		{
			continue;
		}
		m_FrameAni[i]->DeleteAni(_AniName);
	}
}
void RenderParts::LoadSubData(eRednerParts PartNumber, const wchar_t * fileName)
{
	int count = 0;

	BRStream read((PathManager::FindPath(L"SubTransData") + fileName).c_str());
	read.Read(count);
	for (int i = 0; i < count; ++i)
	{
		read.Read(PartSubTrans[PartNumber][i]);
	}
}

void RenderParts::SetPos(const Vector3f & pos)
{
	SubPos = pos;
}

void RenderParts::SettingPart(eRednerParts PartNumber, const wchar_t * SpriteName, const wchar_t * DataName)
{
	LoadSubData(PartNumber, DataName);
	SetSprite(PartNumber, SpriteName);
	PivotUpdate(PartNumber);
}

void RenderParts::PivotUpdate(eRednerParts PartNumber)
{
	size_t curIndex;

	if (m_Render[PartNumber] != nullptr)
	{
		curIndex = m_FrameAni[0]->GetCurIndex();
		Vector2f Pos = PartSubTrans[PartNumber][curIndex];
		Pos.y *= -1.0f;
		Pos += Pivot;
		Pos.x += SubPos.x;
		Pos.y += SubPos.y;

		float dir = m_Trans->GetWorldScale().x >= 0 ? 1.0f : -1.0f;
		m_Render[PartNumber]->SetLocalSubPosition(Vector3f(Pos.x * dir, Pos.y, 0.0f));
		m_Render[PartNumber]->SetLocalSubScale(m_Render[PartNumber]->GetTransform()->GetWorldScale());
		
	}
}

void RenderParts::ChangeAni(const wchar_t * AniName)
{
	for (int i = 0; i < RP_Max; ++i)
	{
		if (m_FrameAni[i] == nullptr)
		{
			continue;
		}
		m_FrameAni[i]->ChangeAni(AniName);
	}
}

bool RenderParts::IsCurAniName(std::wstring AniName)
{
	return m_FrameAni[RP_Skin]->IsCurAniName(AniName);
}
bool RenderParts::IsAniEnd() const
{
	if (m_FrameAni[RP_Skin] == nullptr)
	{
		return true;
	}
	return m_FrameAni[RP_Skin]->IsAniEnd();
}
float RenderParts::CurAniPer()
{
	return m_FrameAni[RP_Skin]->CurAniPer();
}

void RenderParts::AniClear()
{
	for (int i = 0; i < RenderParts::RP_Max; ++i)
	{
		if (m_FrameAni[i] == nullptr)
		{
			continue;
		}
		m_FrameAni[i]->Clear();
	}
}
void RenderParts::AniOff()
{
	for (int i = 0; i < RP_Max; ++i)
	{
		if (m_Render[i] == nullptr)
		{
			continue;
		}
		m_Render[i]->SetUpdate(false);
	}
	for (int i = 0; i < RP_Max; ++i)
	{
		if (m_FrameAni[i] == nullptr)
		{
			continue;
		}
		m_FrameAni[i]->SetUpdate(false);
	}
}
void RenderParts::AniOn()
{
	for (int i = 0; i < RP_Max; ++i)
	{
		if (m_Render[i] == nullptr)
		{
			continue;
		}
		m_Render[i]->SetUpdate(true);
	}
	for (int i = 0; i < RP_Max; ++i)
	{
		if (m_FrameAni[i] == nullptr)
		{
			continue;
		}
		m_FrameAni[i]->SetUpdate(true);
	}
}
void RenderParts::EventDelete(const wchar_t * _AniName, int idx)
{
	m_FrameAni[RP_Skin]->DeleteEvent(_AniName, idx);
}
int RenderParts::FindEventIndex(const wchar_t * AniName, unsigned int _StartFrame, unsigned int _EndFrame)
{
	return m_FrameAni[RP_Skin]->FindEventIndex(AniName,_StartFrame,_EndFrame);
}
SPTR<Com2DFrameAni> RenderParts::GetComFrameAni()
{
	return m_FrameAni[RP_Skin];
}

RenderParts::RenderParts() : Pivot(), PartSubTrans(), SubPos()
{
}
RenderParts::~RenderParts()
{
}
