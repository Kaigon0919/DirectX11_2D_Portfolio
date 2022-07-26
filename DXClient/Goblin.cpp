#include "Goblin.h"
#include"Player.h"
#include<DxDebug.h>
#include<MyRandom.h>
#include<TileMapRender.h>
#include<Level.h>
bool Goblin::Init()
{
	Monster::Init();
	// Move State.
	m_VirPos = Vector3f();
	m_WalkSpeed = 200.0f;

	// Game State Setting.
	m_CurHP = m_MaxHP = 100.0f;

	// Ani.
	ChangeAni(L"Idle");

	HitColPos =(Vector3f(0.0f, 35.0f, 0.0f));
	HitCol->SetLocalSubScale(Vector3f(60.0f, 70.0f, 0.0f));

	StandWaiting.SetTime(1.0f);
	DeadWaiting.SetTime(1.5f);
	SoundPlay(0);
	return true;
}

void Goblin::Update()
{
	Monster::Update();
	if (IsDead())
	{
		if (m_State != GS_DEAD)
			ChangeState(GS_DEAD);
		return;
	}
	if (m_Player != nullptr && (m_State == GS_IDLE || m_State == GS_WALK))
	{
		float dir = m_Player->GetVirtualPosition().x - m_VirPos.x;
		if (dir != 0.0f)
		{
			Vector3f scale = m_Trans->GetWorldScale();
			scale.x = (dir / fabsf(dir));
			m_Trans->SetLocalScale(scale);
		}
	}

}

void Goblin::DebugRender()
{
	DxDebug::DrawRect(GetTransform()->GetWorldPosition(), Vector3f(100.0f, 1.0f, 1.0f), Color4f(1.0f, 0.0f, 0.0f), GetTransform()->GetWorldRotate().z);
	DxDebug::DrawRect(GetTransform()->GetWorldPosition(), Vector3f(1.0f, 100.0f, 1.0f), Color4f(0.0f, 1.0f, 0.0f), GetTransform()->GetWorldRotate().z);
}

void Goblin::FSMUpdate()
{
	switch (m_State)
	{
	case Goblin::GS_IDLE:
		IdleState();
		break;
	case Goblin::GS_WALK:
		WalkState();
		break;
	case Goblin::GS_ATTACK:
		AttackState();
		break;
	case Goblin::GS_HIT:
		HitState();
		break;
	case Goblin::GS_AIRHIT:
		AirHitState();
		break;
	case Goblin::GS_DOWN:
		DownState();
		break;
	case Goblin::GS_STEND:
		StendState();
		break;
	case Goblin::GS_DEAD:
		DeadState();
		break;
	case Goblin::GS_MAX:
		break;
	default:
		break;
	}
}

void Goblin::ChangeState(GoblinState newState)
{
	AttList.clear();
	AttackCol->SetUpdate(false);
	m_State = newState;
	std::wstring aniName;
	switch (m_State)
	{
	case Goblin::GS_IDLE:
		aniName = L"Idle";
		IdleWaiting.Reset();
		SoundPlay(0);
		break;
	case Goblin::GS_WALK:
		aniName = L"Walk";
		WalkWaiting.Reset();
		break;
	case Goblin::GS_ATTACK:
		aniName = L"Attack";
		break;
	case Goblin::GS_HIT:
		aniName = L"Hit";
		SoundPlay(RandomInt(3, 6));
		break;
	case Goblin::GS_AIRHIT:
		aniName = L"AirHit";
		SoundPlay(RandomInt(3, 6));
		break;
	case Goblin::GS_DOWN:
		aniName = L"Down";
		StandWaiting.Reset();
		break;
	case Goblin::GS_STEND:
		aniName = L"Stending";
		StandWaiting.Reset();
		break;
	case Goblin::GS_DEAD:
		DeadWaiting.Reset();
		break;
	case Goblin::GS_MAX:
		break;
	default:
		break;
	}
	if (aniName != L"")
		Parts->ChangeAni(aniName.c_str());
}

void Goblin::IdleState()
{
	if (IdleWaiting.Check())
	{
		ChangeState(GS_WALK);
	}
}

void Goblin::WalkState()
{
	Vector3f dir = m_Player->GetVirtualPosition() - m_VirPos;
	dir.z = 0.0f;
	float dis = dir.Length();
	dir.Normalize();

	if (dis < 300.0f && WalkWaiting.Check())
	{
		ChangeState(GS_IDLE);

	}

	if (WalkRandomCool.Check())
	{

		bool newState = false;
		switch (RandomInt(0, 5))
		{
		case 0:
		case 1:
		case 2:
			if (dis < 50.0f)
			{
				ChangeState(GS_ATTACK);
				newState = true;
			}
			break;
		case 3:
		case 4:
			MoveDirX *= -1.0f;
			break;
		default:
			break;
		}
		WalkRandomCool.Reset();
		if (newState)
		{
			return;
		}
	}


	Vector3f movePos = Vector3f();

	if (dis > 300.0f)
	{
		movePos = dir * (m_WalkSpeed)* TimeManager::GetDeltaTime();
		if (dir.x != 0)
			MoveDirX = dir.x / fabsf(dir.x);
	}
	else
	{
		dir.x = MoveDirX;
		movePos = dir * (m_WalkSpeed)* TimeManager::GetDeltaTime();
	}
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

void Goblin::AttackState()
{
	if (Parts->IsCurAniName(L"Attack") && Parts->IsAniEnd())
	{
		ChangeState(GS_WALK);
	}
	HitInfo info;
	info.Damage = 10.0f;
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

void Goblin::HitState()
{
	if (m_Force.Length() < 1.0f && StunWaiting.Check())
	{
		ChangeState(GS_IDLE);
	}
}

void Goblin::AirHitState()
{
	if (m_bGorund && m_Force.z <= 0.0f)
	{
		ChangeState(GS_DOWN);
	}
}

void Goblin::DownState()
{
	if (StandWaiting.Check())
	{
		ChangeState(GS_STEND);
	}
}

void Goblin::StendState()
{
	if (StandWaiting.Check())
	{
		ChangeState(GS_IDLE);
	}
}

void Goblin::DeadState()
{
	if (DeadWaiting.Check())
	{
		SoundPlay(RandomInt(1, 2));
		GetActor()->SetUpdate(false);
		AttList.clear();
	}
}
void Goblin::AttackEnter(ComCol * thisCol, ComCol * OtherCol)
{
	BattlePawn::AttackEnter(thisCol, OtherCol);
}
void Goblin::AttackStay(ComCol * thisCol, ComCol * OtherCol)
{
	BattlePawn::AttackEnter(thisCol, OtherCol);
}
void Goblin::AttackExit(ComCol * thisCol, ComCol * OtherCol)
{
	BattlePawn::AttackEnter(thisCol, OtherCol);
}
void Goblin::HitEnter(ComCol * thisCol, ComCol * OtherCol)
{
}
void Goblin::HitStay(ComCol * thisCol, ComCol * OtherCol)
{
}
void Goblin::HitExit(ComCol * thisCol, ComCol * OtherCol)
{
}
void Goblin::DamageProcess(HitInfo info)
{
	float endDamage = info.Damage + (float)RandomInt(-3, 0);
	m_CurHP -= endDamage;
	m_CurHP = m_CurHP < 0.0f ? 0.0f : m_CurHP;
	AddForce(info.ForceVec);
	StunWaiting.SetTime(info.HitStunTime);
	StunWaiting.Reset();
	switch (info.state)
	{
	case BattlePawn::HS_KNOCKBACK:
		if (m_State != GS_AIRHIT && m_State != GS_DOWN && m_bGorund)
			ChangeState(GS_HIT);
		else
		{
			if (m_State == GS_DOWN)
			{
				AddForce(Vector3f(0.0f, 0.0f, fabsf(info.ForceVec.x)));
			}
			else
			{
				AddForce(Vector3f(0.0f, 0.0f, fabsf(info.ForceVec.x) * (500.0f / fabsf(info.ForceVec.x))));
			}
			ChangeState(GS_AIRHIT);
		}
		break;
	case BattlePawn::HS_THROWKNOCKBACK:
		ChangeState(GS_AIRHIT);
		break;
	case BattlePawn::HS_AIRBORNE:
		ChangeState(GS_AIRHIT);
		break;
	case BattlePawn::HS_MAX:
		break;
	default:
		break;
	}
	SPTR<Actor> ptr = GetActor()->GetLevel()->CreateActor(0);
	ptr->GetTransform()->SetWorldPosition(m_Trans->GetWorldPosition() + Vector3f(-55.0f, 40.0f, -10.0f) + Vector3f((float)RandomInt(-30, 30), (float)RandomInt(-30, 30), 0.0f));
	SPTR<DamageNumber> comPtr = ptr->AddComponent<DamageNumber>();
	comPtr->InitSetting(4, L"DamageFont.png", (int)endDamage);
	comPtr->SetVelocity(Vector3f(0.0f, 100.0f, 0.0f));
}
void Goblin::SoundPlay(size_t number)
{
	switch (number)
	{
	case 0:
		m_Sound->Play(L"gbn_comm.ogg");
		break;
	case 1:
		m_Sound->Play(L"gbn_die_01.ogg");
		break;
	case 2:
		m_Sound->Play(L"gbn_die_02.ogg");
		break;
	case 3:
		m_Sound->Play(L"gbn_dmg_01.ogg");
		break;
	case 4:
		m_Sound->Play(L"gbn_dmg_02.ogg");
		break;
	case 5:
		m_Sound->Play(L"gbn_dmg_03.ogg");
		break;
	case 6:
		m_Sound->Play(L"gbn_dmg_04.ogg");
		break;
	case 7:
		m_Sound->Play(L"gbn_thw.ogg");
		break;
	default:
		break;
	}
}
Goblin::Goblin() : MoveDirX(1.0f), IdleWaiting(0.5f), WalkWaiting(5.0f), WalkRandomCool(1.0f)
{

}


Goblin::~Goblin()
{
}
