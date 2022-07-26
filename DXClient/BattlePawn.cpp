#include "BattlePawn.h"

#include<RenderParts.h>
#include<PathManager.h>
#include<BRStream.h>
#include<Col2DRect.h>
#include<TileMapRender.h>
#include"BackGround.h"

bool BattlePawn::Init()
{

	m_Gravity = -980.0f;

	m_Trans = GetComponent<Transform>();
	// RenderParts Add.
	Parts = AddComponent<RenderParts>();
	// Sound
	m_Sound = AddComponent<MySoundPlayer>();
	return false;
}

void BattlePawn::Update()
{
	if (!m_bGorund)
	{
		m_Force.z += (m_Gravity  * TimeManager::GetDeltaTime());
	}
	if (m_Force.Length() > 0.003f)
	{
		Vector3f movePos = m_Force * TimeManager::GetDeltaTime();
		Vector3f axis = Vector3f();
		if (m_TileMap != nullptr)
		{
			for (int i = 0; i < 2; ++i)
			{
				axis = Vector3f();
				axis[i] = m_Force[i] * TimeManager::GetDeltaTime();
				if (m_TileMap->GetTileState(Vector2i((int)(m_VirPos.x + axis.x), (int)(m_VirPos.y + axis.y))) == 1)
				{
					movePos -= axis;
				}
			}
		}

		VirMove(movePos);
		m_Force.x *= 0.9f;
	}
	else
	{
		m_Force = Vector3f::Zero;
	}
	if ((m_VirPos.z <= 0.0f) && (m_Force.z <= 0.0f))
	{
		m_bGorund = true;
		m_Force.z = 0.0f;
		m_VirPos.z = m_VirPos.z < 0.0f ? 0.0f : m_VirPos.z;
	}
	else
	{
		m_bGorund = false;
	}
}

void BattlePawn::LateUpdate()
{
	FSMUpdate();
	VirPosUpdate();
}

void BattlePawn::VirMove(float x, float y, float z)
{
	m_VirPos.x += x;
	m_VirPos.y += y;
	m_VirPos.z += z;
}

void BattlePawn::VirMove(const Vector3f & velue)
{
	m_VirPos += velue;
}

void BattlePawn::VirPosUpdate()
{
	m_Trans->SetWorldPosition(m_VirPos.x, m_VirPos.y, 0.0f);
	Parts->SetPos(Vector3f(0.0f, m_VirPos.z, 0.0f));
	AttackCol->SetLocalSubPosition(AttackColPos + Vector3f(0.0f,m_VirPos.z, 0.0f));
	HitCol->SetLocalSubPosition(HitColPos + Vector3f(0.0f, m_VirPos.z, 0.0f));
}

void BattlePawn::ChangeAni(const wchar_t * AniName)
{
	Parts->ChangeAni(AniName);
}

void BattlePawn::EventOn(void * Data)
{
	AniEventData* eData = (AniEventData*)Data;
	if (AttackCol != nullptr)
	{
		AttackColPos = Vector3f{ eData->Position.x * GetTransform()->GetWorldScale().x, eData->Position.y,0.0f };
		AttackCol->SetLocalSubPosition(Vector3f{ AttackColPos.x, AttackColPos.y + m_VirPos.z,0.0f });
		AttackCol->SetLocalSubScale(Vector3f{ eData->Scale.x, eData->Scale.y ,1.0f });
		AttackCol->SetUpdate(true);
	}
}

void BattlePawn::EventOff(void * Data)
{
	if (AttackCol != nullptr)
	{
		AttackCol->SetUpdate(false);
	}

	std::list<AttListInfo>::iterator itStart = AttList.begin();
	while (itStart != AttList.end())
	{
		(*itStart).m_AttackTaget->CallEraseOtherList(this);
		itStart = AttList.erase(itStart);
	}
}

void BattlePawn::AniLoad(const wchar_t * AniData)
{
	Parts = GetComponent<RenderParts>();
	if (Parts == nullptr)
	{
		return;
	}
	std::wstring Path = PathManager::FindPath(L"AniData") + AniData;

	BRStream Stream = BRStream(Path.c_str());

	Vector2i pivot;
	Stream.Read(pivot);
	Parts->SetPivot(pivot);

	int size;
	int eventSize;
	Stream.Read(size);

	SaveAniData MyLoadData = {};
	AniEventData EventData;

	for (int i = 0; i < size; ++i)
	{
		Stream.Read(MyLoadData);
		Parts->CreateAni(MyLoadData.AniName, MyLoadData.StartFrame, MyLoadData.EndFrame, MyLoadData.isLoop, MyLoadData.DefTime);

		Stream.Read(eventSize);
		for (int j = 0; j < eventSize; ++j)
		{
			Stream.Read(EventData);
			AniEventData* ptr = new AniEventData;
			ptr->StartFrame = EventData.StartFrame;
			ptr->EndFrame = EventData.EndFrame;
			ptr->Position = EventData.Position;
			ptr->Scale = EventData.Scale;

			Parts->SetFrameEvent(MyLoadData.AniName, ptr->StartFrame, ptr->EndFrame, &BattlePawn::EventOn, this, ptr);
			Parts->SetFrameEvent(MyLoadData.AniName, ptr->EndFrame, ptr->EndFrame, &BattlePawn::EventOff, this, nullptr);

			EventDataList.push_back(ptr);
		}
	}
}

void BattlePawn::AttackEnter(ComCol * thisCol, ComCol * OtherCol)
{
	SPTR<BattlePawn> taget = OtherCol->GetActor()->GetComponent<BattlePawn>();
	if (taget == nullptr)
	{
		return;
	}
	if (fabsf(taget->GetVirtualPosition().y - m_VirPos.y) > 50.0f)
		return;

	std::list<AttListInfo>::iterator itStart = AttList.begin();
	while (itStart != AttList.end())
	{
		if ((*itStart).m_AttackTaget == taget.Get())
		{
			break;
		}
		++itStart;
	}
	if (itStart == AttList.end())
	{
		AttListInfo info;
		info.isHit = false;
		info.m_AttackTaget = taget.Get();
		AttList.push_back(info);
		taget->OtherAttList.push_back(this);
	}
}

void BattlePawn::AttackStay(ComCol * thisCol, ComCol * OtherCol)
{
	SPTR<BattlePawn> taget = OtherCol->GetActor()->GetComponent<BattlePawn>();
	if (taget == nullptr)
	{
		return;
	}
	std::list<AttListInfo>::iterator itStart = AttList.begin();
	while (itStart != AttList.end())
	{
		if ((*itStart).m_AttackTaget == taget.Get())
		{
			break;
		}
		++itStart;
	}
	if (itStart == AttList.end())
	{
		if (fabsf(taget->GetVirtualPosition().y - m_VirPos.y) > 50.0f)
			return;
		else
		{
			AttListInfo info;
			info.isHit = false;
			info.m_AttackTaget = taget.Get();
			AttList.push_back(info);
			taget->OtherAttList.push_back(this);
		}
	}
}

void BattlePawn::AttackExit(ComCol * thisCol, ComCol * OtherCol)
{
	if (OtherCol == nullptr)
	{
		return;
	}
	SPTR<BattlePawn> taget = OtherCol->GetActor()->GetComponent<BattlePawn>();
	if (taget == nullptr)
	{
		return;
	}
	if (AttList.size() <= 0)
	{
		return;
	}
	std::list<AttListInfo>::iterator itStart = AttList.begin();
	while (itStart != AttList.end())
	{
		if ((*itStart).m_AttackTaget == taget.Get())
		{
			if ((*itStart).isHit == false)
			{
				itStart = AttList.erase(itStart);
				taget->CallEraseOtherList(this);
			}
			break;
		}
		++itStart;
	}
}

void BattlePawn::EventDataClear()
{
	std::list<AniEventData*>::iterator itStart = EventDataList.begin();
	std::list<AniEventData*>::iterator itEnd = EventDataList.end();

	while (itStart != itEnd)
	{
		if ((*itStart) != nullptr)
		{
			delete *itStart;
		}
		++itStart;
	}
	EventDataList.clear();
}

void BattlePawn::SetBackground(Actor * back)
{
	m_Backgorund = back->GetComponent<BackGround>();
	m_TileMap = back->GetComponent<TileMapRender>();
}
void BattlePawn::DamageProcess(HitInfo info)
{

}
void BattlePawn::CallEraseAttList(const BattlePawn * taget)
{
	std::list<AttListInfo>::iterator itStart = AttList.begin();
	while (itStart != AttList.end())
	{
		if ((*itStart).m_AttackTaget == taget)
		{
			AttList.erase(itStart);
			break;
		}
		++itStart;
	}
}
void BattlePawn::CallEraseOtherList(const BattlePawn * taget)
{
	std::list<BattlePawn*>::iterator itStart = OtherAttList.begin();
	while (itStart != OtherAttList.end())
	{
		if ((*itStart) == taget)
		{
			OtherAttList.erase(itStart);
			break;
		}
		++itStart;
	}
}
BattlePawn::BattlePawn()
{
}


BattlePawn::~BattlePawn()
{
	EventDataClear();
	AttList.clear();

	/*std::list<BattlePawn*>::iterator itStart = OtherAttList.begin();
	while (itStart != OtherAttList.end())
	{
		(*itStart)->CallEraseAttList(this);
		++itStart;
	}*/
}
