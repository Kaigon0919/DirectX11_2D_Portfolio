#include "Tau.h"
#include<TileMapRender.h>
#include<DxDebug.h>
#include<MyRandom.h>
#include<Level.h>
Tau::Tau() : MoveDirX(1.0f), IdleWaiting(0.5f), WalkWaiting(5.0f), WalkRandomCool(0.5f), SuperArmorTime(5.0f), SACount(0) , m_bSuperArmor(false)
{
}


Tau::~Tau()
{
}

bool Tau::Init()
{
	Monster::Init();
	// Move State.
	m_VirPos = Vector3f();
	m_WalkSpeed = 200.0f;
	m_RushSpeed = 500.0f;

	// Game State Setting.
	m_CurHP = m_MaxHP = 250.0f;

	// Ani.
	ChangeAni(L"Idle");

	HitColPos = (Vector3f(0.0f, 70.0f, 0.0f));
	HitCol->SetLocalSubScale(Vector3f(100.0f, 180.0f, 0.0f));

	StandWaiting.SetTime(1.0f);
	DeadWaiting.SetTime(1.5f);
	SoundPlay(1);
	return true;
}

void Tau::Update()
{
	Monster::Update();
	if (IsDead())
	{
		SACount = 0;
		m_bSuperArmor = false;

		if (m_State != TS_DEAD)
			ChangeState(TS_DEAD);
		return;
	}
	if (m_Player != nullptr && (m_State == TS_IDLE || m_State == TS_WALK))
	{
		float dir = m_Player->GetVirtualPosition().x - m_VirPos.x;
		if (dir != 0.0f)
		{
			Vector3f scale = m_Trans->GetWorldScale();
			scale.x = (dir / fabsf(dir));
			m_Trans->SetLocalScale(scale);
		}
	}

	if (SuperArmorTime.Check())
	{
		m_bSuperArmor = false;
	}
	if (SACount >= 5)
	{
		SACount -= 5;
		SuperArmorTime.Reset();
		m_bSuperArmor = true;
	}

}

void Tau::DebugRender()
{
	DxDebug::DrawRect(GetTransform()->GetWorldPosition(), Vector3f(100.0f, 1.0f, 1.0f), Color4f(1.0f, 0.0f, 0.0f), GetTransform()->GetWorldRotate().z);
	DxDebug::DrawRect(GetTransform()->GetWorldPosition(), Vector3f(1.0f, 100.0f, 1.0f), Color4f(0.0f, 1.0f, 0.0f), GetTransform()->GetWorldRotate().z);
}

void Tau::FSMUpdate()
{
	switch (m_State)
	{
	case Tau::TS_IDLE:
		IdleState();
		break;
	case Tau::TS_WALK:
		WalkState();
		break;
	case Tau::TS_ATTACK:
		AttackState();
		break;
	case Tau::TS_HIT:
		HitState();
		break;
	case Tau::TS_AIRHIT:
		AirHitState();
		break;
	case Tau::TS_DOWN:
		DownState();
		break;
	case Tau::TS_ROAR:
		RoarState();
		break;
	case Tau::TS_RUSH:
		RushState();
		break;
	case Tau::TS_STEND:
		StendState();
		break;
	case Tau::TS_DEAD:
		DeadState();
		break;
	case Tau::TS_MAX:
		break;
	default:
		break;
	}
}

void Tau::ChangeState(TauState newState)
{
	AttList.clear();
	AttackCol->SetUpdate(false);
	m_State = newState;
	std::wstring aniName;
	switch (m_State)
	{
	case Tau::TS_IDLE:
		aniName = L"Idle";
		IdleWaiting.Reset();
		SoundPlay(1);
		break;
	case Tau::TS_WALK:
		aniName = L"Walk";
		WalkWaiting.Reset();
		break;
	case Tau::TS_ATTACK:
		aniName = L"Attack";
		SoundPlay(0);
		break;
	case Tau::TS_HIT:
		aniName = L"Hit";
		SoundPlay(RandomInt(4,6));
		break;
	case Tau::TS_AIRHIT:
		aniName = L"AirHit";
		SoundPlay(RandomInt(4, 6));
		break;
	case Tau::TS_DOWN:
		aniName = L"Down";
		break;
	case Tau::TS_ROAR:
		aniName = L"Roar";
		SoundPlay(7);
		break;
	case Tau::TS_RUSH:
		aniName = L"Rush";
		SoundPlay(8);
		break;
	case Tau::TS_STEND:
		aniName = L"Standing";
		break;
	case Tau::TS_DEAD:
		SoundPlay(3);
		break;
	case Tau::TS_MAX:
		break;
	default:
		break;
	}
	if (aniName != L"")
		Parts->ChangeAni(aniName.c_str());
}

void Tau::IdleState()
{
	if (IdleWaiting.Check())
	{
		ChangeState(TS_WALK);
	}
}

void Tau::WalkState()
{
	Vector3f dir = m_Player->GetVirtualPosition() - m_VirPos;
	dir.z = 0.0f;
	float dis = dir.Length();
	dir.Normalize();

	if (dis < 300.0f && WalkWaiting.Check())
	{
		ChangeState(TS_IDLE);
	}

	if (WalkRandomCool.Check())
	{
		bool newState = false;
		switch (RandomInt(0, 9))
		{
		case 0:
			MoveDirX = dir.x / fabsf(dir.x);
			break;
		case 1:
			MoveDirX *= -1.0f;
			break;
		case 2:
		case 3:
		case 4:
		case 5:
			if (dis < 200.0f)
			{
				ChangeState(TS_ATTACK);
				newState = true;
			}
			break;
		case 6:
		case 7:
			if (dis < 180.0f)
			{
				ChangeState(TS_ROAR);
				newState = true;
			}
			break;
		case 8:
			if (dis < 250.0f)
			{
				ChangeState(TS_RUSH);
				newState = true;
			}
			break;
		default:
			MoveDirX = dir.x / fabsf(dir.x);
			break;
		}
		WalkRandomCool.Reset();
		if (newState)
		{
			return;
		}
	}

	Vector3f movePos = Vector3f();
	// 거리가 300이상이면 무조건 플레이어한테 간다.
	if (dis > 500.0f)
	{
		movePos = dir * (m_WalkSpeed)* TimeManager::GetDeltaTime();
		if (dir.x != 0)
			MoveDirX = dir.x / fabsf(dir.x);
	}
	else
	{
		// 아니라면 랜덤으로 앞뒤로 이동한다.
		dir.x = MoveDirX;
		movePos = dir * (m_WalkSpeed)* TimeManager::GetDeltaTime();
	}

	// 타일맵 충돌.
	Vector3f axis = Vector3f();
	if (m_TileMap != nullptr)
	{
		for (int i = 0; i < 2; ++i)
		{
			axis = Vector3f();
			axis[i] = dir[i] * (m_WalkSpeed)* TimeManager::GetDeltaTime();
			if (m_TileMap->GetTileState(Vector2i((int)(m_VirPos.x + axis.x), (int)(m_VirPos.y + axis.y))) == 1)
			{
				movePos -= axis;
			}
		}
	}
	VirMove(movePos);
}

void Tau::AttackState()
{
	if (Parts->IsCurAniName(L"Attack") && Parts->IsAniEnd())
	{
		ChangeState(TS_WALK);
	}
	HitInfo info;
	info.Damage = 15.0f;
	info.ForceVec = Vector3f(100.0f, 0.0f, 0.0f);
	info.ForceVec.x *= m_Trans->GetWorldScale().x;
	info.HitStunTime = 0.6f;
	info.state = HitState::HS_KNOCKBACK;

	std::list<AttListInfo>::iterator itStart = AttList.begin();
	std::list<AttListInfo>::iterator itEnd = AttList.end();
	for (; itStart != itEnd; ++itStart)
	{
		if ((*itStart).isHit == false)
		{
			(*itStart).m_AttackTaget->DamageProcess(info);
			(*itStart).isHit = true;
		}
	}
}

void Tau::HitState()
{
	if (m_Force.Length() < 1.0f && StunWaiting.Check())
	{
		ChangeState(TS_IDLE);
	}
}

void Tau::AirHitState()
{
	if (m_bGorund && m_Force.z <= 0.0f)
	{
		ChangeState(TS_DOWN);
	}
}

void Tau::RoarState()
{
	if (Parts->IsCurAniName(L"Roar") && Parts->IsAniEnd())
	{
		ChangeState(TS_IDLE);
	}
	HitInfo info;
	info.Damage = 10.0f;
	info.ForceVec = Vector3f(100.0f, 0.0f, 0.0f);
	info.ForceVec.x *= m_Trans->GetWorldScale().x;
	info.HitStunTime = 1.5f;
	info.state = HitState::HS_KNOCKBACK;

	std::list<AttListInfo>::iterator itStart = AttList.begin();
	std::list<AttListInfo>::iterator itEnd = AttList.end();
	for (; itStart != itEnd; ++itStart)
	{
		if ((*itStart).isHit == false)
		{
			(*itStart).m_AttackTaget->DamageProcess(info);
			(*itStart).isHit = true;
		}
	}
}

void Tau::RushState()
{
	if (Parts->IsCurAniName(L"Rush") && Parts->IsAniEnd())
	{
		ChangeState(TS_IDLE);
	}

	//
	Vector3f dir = Vector3f(m_Trans->GetWorldScale().x, 0.0f, 0.0f);
	Vector3f movePos = Vector3f();

	movePos = dir * (m_RushSpeed)* TimeManager::GetDeltaTime();

	Vector3f axis = Vector3f();
	if (m_TileMap != nullptr)
	{
		for (int i = 0; i < 2; ++i)
		{
			axis = Vector3f();
			axis[i] = dir[i] * (m_WalkSpeed)* TimeManager::GetDeltaTime();
			if (m_TileMap->GetTileState(Vector2i((int)(m_VirPos.x + axis.x), (int)(m_VirPos.y + axis.y))) == 1)
			{
				movePos -= axis;
			}
		}
	}
	VirMove(movePos);

	HitInfo info;
	info.Damage = 30.0f;
	info.ForceVec = Vector3f(600.0f, 0.0f, 600.0f);
	info.ForceVec.x *= m_Trans->GetWorldScale().x;
	info.HitStunTime = 0.6f;
	info.state = HitState::HS_AIRBORNE;

	std::list<AttListInfo>::iterator itStart = AttList.begin();
	std::list<AttListInfo>::iterator itEnd = AttList.end();
	for (; itStart != itEnd; ++itStart)
	{
		if ((*itStart).isHit == false)
		{
			(*itStart).m_AttackTaget->DamageProcess(info);
			(*itStart).isHit = true;
		}
	}
}

void Tau::DownState()
{
	if (StandWaiting.Check())
	{
		ChangeState(TS_STEND);
	}
}

void Tau::StendState()
{
	if (StandWaiting.Check())
	{
		ChangeState(TS_IDLE);
	}
}

void Tau::DeadState()
{
	if (DeadWaiting.Check())
	{
		SoundPlay(RandomInt(1, 2));
		GetActor()->SetUpdate(false);
	}
}

void Tau::AttackEnter(ComCol * thisCol, ComCol * OtherCol)
{
	BattlePawn::AttackEnter(thisCol, OtherCol);
}

void Tau::AttackStay(ComCol * thisCol, ComCol * OtherCol)
{
	BattlePawn::AttackStay(thisCol, OtherCol);
}

void Tau::AttackExit(ComCol * thisCol, ComCol * OtherCol)
{
	BattlePawn::AttackExit(thisCol, OtherCol);
}

void Tau::HitEnter(ComCol * thisCol, ComCol * OtherCol)
{
}

void Tau::HitStay(ComCol * thisCol, ComCol * OtherCol)
{
}

void Tau::HitExit(ComCol * thisCol, ComCol * OtherCol)
{
}

void Tau::DamageProcess(HitInfo info)
{
	float endDamage = info.Damage + (float)RandomInt(-5, 0);
	m_CurHP -= endDamage;
	m_CurHP = m_CurHP < 0.0f ? 0.0f : m_CurHP;

	if (!m_bSuperArmor)
	{
		AddForce(info.ForceVec);
		StunWaiting.SetTime(info.HitStunTime);
		StunWaiting.Reset();
		switch (info.state)
		{
		case BattlePawn::HS_KNOCKBACK:
			if (m_State != TS_AIRHIT && m_State != TS_DOWN)
				ChangeState(TS_HIT);
			else
			{
				if (m_State == TS_DOWN)
				{
					AddForce(Vector3f(0.0f, 0.0f, fabsf(info.ForceVec.x)));
				}
				else
				{
					AddForce(Vector3f(0.0f, 0.0f, fabsf(info.ForceVec.x) * (500.0f / fabsf(info.ForceVec.x))));
				}
				ChangeState(TS_AIRHIT);
			}
			break;
		case BattlePawn::HS_THROWKNOCKBACK:
			ChangeState(TS_AIRHIT);
			break;
		case BattlePawn::HS_AIRBORNE:
			ChangeState(TS_AIRHIT);
			break;
		case BattlePawn::HS_MAX:
			break;
		default:
			break;
		}
		//++SACount;
	}
	SPTR<Actor> ptr = GetActor()->GetLevel()->CreateActor(0);
	ptr->GetTransform()->SetWorldPosition(m_Trans->GetWorldPosition() + Vector3f(-55.0f, 70.0f, -10.0f) + Vector3f((float)RandomInt(-30, 30), (float)RandomInt(-30, 30), 0.0f));
	SPTR<DamageNumber> comPtr = ptr->AddComponent<DamageNumber>();
	comPtr->InitSetting(4, L"DamageFont.png", (int)info.Damage);
	comPtr->SetVelocity(Vector3f(0.0f, 100.0f, 0.0f));
}

void Tau::SoundPlay(size_t number)
{
	switch (number)
	{
	case 0:
		m_Sound->Play(L"tau_axeswing.ogg");
		break;
	case 1:
		m_Sound->Play(L"tau_comm.ogg");
		break;
	case 2:
		m_Sound->Play(L"tau_crash.ogg");
		break;
	case 3:
		m_Sound->Play(L"tau_die.ogg");
		break;
	case 4:
		m_Sound->Play(L"tau_dmg_01.ogg");
		break;
	case 5:
		m_Sound->Play(L"tau_dmg_02.ogg");
		break;
	case 6:
		m_Sound->Play(L"tau_dmg_03.ogg");
		break;
	case 7:
		m_Sound->Play(L"tau_roar.ogg");
		break;
	case 8:
		m_Sound->Play(L"tau_rush.ogg");
		break;
	default:
		break;
	}
}