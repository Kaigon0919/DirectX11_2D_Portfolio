#include"Player.h"
#include<Com2DFrameAni.h>
#include<TileMapRender.h>
#include<MySoundPlayer.h>
#include<MyRandom.h>
#include<Level.h>
#include"Fade.h"
void Player::FSMUpdate()
{
	switch (m_State)
	{
	case Player::PLAYER_IDLE:
		IdleState();
		break;
	case Player::PLAYER_BATTLEIDLE:
		BattleState();
		break;
	case Player::PLAYER_WALK:
		WalkState();
		break;
	case Player::PLAYER_RUN:
		RunState();
		break;
	case Player::PLAYER_JUMP:
		JumpState();
		break;
	case Player::PLAYER_JUMPATTACK:
		JumpAttackState();
		break;
	case Player::PLAYER_Attack01:
		Attack01State();
		break;
	case Player::PLAYER_Attack02:
		Attack02State();
		break;
	case Player::PLAYER_Attack04:
		Attack04State();
		break;
	case Player::PLAYER_Attack08:
		Attack08State();
		break;
	case Player::PLAYER_HIT:
		HitState();
		break;
	case Player::PLAYER_AIRHIT:
		AirHitState();
		break;
	case Player::PLAYER_DOWN:
		DownState();
		break;
	case Player::PLAYER_Skill01:
		Skill01State();
		break;
	case Player::PLAYER_Skill02:
		Skill02State();
		break;
	case Player::PLAYER_DEAD:
		DeadState();
	case Player::PLAYER_MAX:
		break;
	default:
		break;
	}
}

void Player::ChangeState(PlayerState newState)
{
	m_Effect->DeleteAllPart();
	AttackCol->SetUpdate(false);
	AttList.clear();
	m_State = newState;
	std::wstring aniName;
	TimerSet();
	if (newState == PLAYER_IDLE && m_bBattle)
	{
		m_State = PLAYER_BATTLEIDLE;
	}
	switch (m_State)
	{
	case Player::PLAYER_IDLE:
		aniName = L"Idle";
		break;
	case Player::PLAYER_BATTLEIDLE:
		aniName = L"BattleIdle";
		break;
	case Player::PLAYER_WALK:
		aniName = L"Walk";
		break;
	case Player::PLAYER_RUN:
		aniName = L"Run";
		break;
	case Player::PLAYER_JUMP:
		SoundPlay(3);
		aniName = L"JumpStart";
		break;
	case Player::PLAYER_JUMPATTACK:
		SoundPlay(RandomInt(4, 5));
		aniName = L"JumpAttack";
		WeaponSound(RandomInt(0, 1));
		break;
	case Player::PLAYER_Attack01:
		aniName = L"Attack01";
		SoundPlay(RandomInt(0, 2));
		WeaponSound(RandomInt(0, 1));
		break;
	case Player::PLAYER_Attack02:
		aniName = L"Attack02";
		SoundPlay(RandomInt(0, 2));
		WeaponSound(RandomInt(0, 1));
		break;
	case Player::PLAYER_Attack04:
		aniName = L"Attack04";
		SoundPlay(RandomInt(0, 2));
		WeaponSound(RandomInt(0, 1));
		break;
	case Player::PLAYER_Attack08:
		aniName = L"Attack08";
		SoundPlay(7);
		WeaponSound(RandomInt(0, 1));
		break;
	case Player::PLAYER_HIT:
		aniName = L"Hit";
		break;
	case Player::PLAYER_AIRHIT:
		aniName = L"AirHit";
		break;
	case Player::PLAYER_DOWN:
		aniName = L"Down";
		break;
	case Player::PLAYER_Skill01:
		aniName = L"Attack05";
		SoundPlay(6);
		WeaponSound(RandomInt(0, 1));
		m_Effect->DeleteAllPart();
		m_Effect->SettingPart(RenderParts::RP_Skin, L"upperslash.png", L"upperslash.data");
		m_Effect->SetPivot(Vector2i(130, 55));
		m_Effect->CreateAni(L"upperslash", 4, 8, false);
		m_Effect->ChangeAni(L"upperslash");
		m_Effect->AniOff();
		break;
	case Player::PLAYER_Skill02:
		aniName = L"Attack12";
		SoundPlay(RandomInt(7, 8));
		m_Effect->DeleteAllPart();
		m_Effect->SetPivot(Vector2i(15, 85));
		m_Effect->SettingPart(RenderParts::RP_Skin, L"hardattackblade1.png", L"hardattackblade1.data");
		m_Effect->SettingPart(RenderParts::RP_Hair, L"hardattackblade2.png", L"hardattackblade2.data");
		m_Effect->CreateAni(L"hardattack", 0, 5, false);
		m_Effect->ChangeAni(L"hardattack");
		m_Effect->ChangeAni(L"hardattack");
		m_Effect->AniOff();
		break;
	case Player::PLAYER_DEAD:
		DeadTime.Reset();
		FadeStartWating.Reset();
		SoundPlay(9);
		break;
	case Player::PLAYER_MAX:
		break;
	default:
		break;
	}
	if(aniName != L"")
		Parts->ChangeAni(aniName.c_str());
}

void Player::IdleState()
{
	RunWaitingTime -= TimeManager::GetDeltaTime();
	RunWaitingTime = RunWaitingTime < -10.0f ? -10.f : RunWaitingTime;

	if (InputMoveFunction().Length() > 0.1f)
	{
		if (RunWaitingTime >= 0.0f)
			ChangeState(PLAYER_RUN);
		else
			ChangeState(PLAYER_WALK);
	}
	if (InputManager::IsPressed(L"C"))
	{
		Jump();
		ChangeState(PLAYER_JUMP);
	}
	if (InputManager::IsPressed(L"X"))
	{
		ChangeState(PLAYER_Attack01);
	}
}
void Player::BattleState()
{
	RunWaitingTime -= TimeManager::GetDeltaTime();
	RunWaitingTime = RunWaitingTime < -10.0f ? -10.f : RunWaitingTime;

	if (InputMoveFunction().Length() > 0.1f)
	{
		if (RunWaitingTime >= 0.0f)
			ChangeState(PLAYER_RUN);
		else
			ChangeState(PLAYER_WALK);
	}
	if (InputManager::IsPressed(L"C"))
	{
		Jump();
		ChangeState(PLAYER_JUMP);
	}
	if (InputManager::IsPressed(L"X"))
	{
		ChangeState(PLAYER_Attack01);
	}
}
void Player::WalkState()
{
	if (InputManager::IsPressed(L"C"))
	{
		Jump();
		ChangeState(PLAYER_JUMP);
	}
	if (InputManager::IsPressed(L"X"))
	{
		Vector3f focDir;
		focDir.x = m_Trans->GetWorldScale().x * 80.0f;
		AddForce(focDir);
		ChangeState(PLAYER_Attack01);
		return;
	}
	Vector3f dir = InputMoveFunction();

	if (dir.x < 0 && m_Trans->GetWorldScale().x > 0)
	{
		m_Trans->SetLocalScale(-1.0f, 1.0f, 1.0f);
	}
	else if (dir.x > 0 && m_Trans->GetWorldScale().x < 0)
	{
		m_Trans->SetLocalScale(1.0f, 1.0f, 1.0f);
	}
	dir.Normalize();

	if (dir.Length() < 0.1f)
	{
		RunWaitingTime = 0.2f;
		ChangeState(PLAYER_IDLE);
	}
	else
	{
		Vector3f movePos = dir * (m_WalkSpeed)* TimeManager::GetDeltaTime();
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
}
void Player::RunState()
{
	if (InputManager::IsPressed(L"C"))
	{
		Jump();
		ChangeState(PLAYER_JUMP);
	}
	if (InputManager::IsPressed(L"X"))
	{
		Vector3f focDir;
		focDir.x = m_Trans->GetWorldScale().x * 200.0f;
		AddForce(focDir);
		ChangeState(PLAYER_Attack08);
		return;
	}
	Vector3f dir = InputMoveFunction();

	if (dir.x < 0 && m_Trans->GetWorldScale().x > 0)
	{
		m_Trans->SetLocalScale(-1.0f, 1.0f, 1.0f);
	}
	else if (dir.x > 0 && m_Trans->GetWorldScale().x < 0)
	{
		m_Trans->SetLocalScale(1.0f, 1.0f, 1.0f);
	}
	dir.Normalize();

	if (dir.Length() < 0.1f)
	{
		ChangeState(PLAYER_IDLE);
	}
	else
	{
		Vector3f movePos = dir * (m_RunSpeed)* TimeManager::GetDeltaTime();
		Vector3f axis = Vector3f();
		if (m_TileMap != nullptr)
		{
			for (int i = 0; i < 2; ++i)
			{
				axis = Vector3f();
				axis[i] = dir[i] * (m_RunSpeed)* TimeManager::GetDeltaTime();
				if (m_TileMap->GetTileState(Vector2i((int)(m_VirPos.x + axis.x), (int)(m_VirPos.y + axis.y))) == 1)
				{
					movePos -= axis;
				}
			}
		}
		VirMove(movePos);
	}
}
void Player::JumpState()
{
	if (m_JumpVelocity < -4 && Parts->IsCurAniName(L"JumpStart"))
	{
		ChangeAni(L"JumpEnd");
	}
	if (m_bGorund)
	{
		ChangeState(PLAYER_IDLE);
	}
	if (InputManager::IsPressed(L"X"))
	{
		ChangeState(PLAYER_JUMPATTACK);
	}

	Vector3f dir = InputMoveFunction();

	if (dir.x < 0 && m_Trans->GetWorldScale().x > 0)
	{
		m_Trans->SetLocalScale(-1.0f, 1.0f, 1.0f);
	}
	else if (dir.x > 0 && m_Trans->GetWorldScale().x < 0)
	{
		m_Trans->SetLocalScale(1.0f, 1.0f, 1.0f);
	}
	dir.Normalize();

	Vector3f movePos = dir * (m_WalkSpeed)* TimeManager::GetDeltaTime();
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
void Player::JumpAttackState()
{
	if (m_bGorund)
	{
		Vector3f dir = InputMoveFunction();

		if (dir.x < 0 && m_Trans->GetWorldScale().x > 0)
		{
			m_Trans->SetLocalScale(-1.0f, 1.0f, 1.0f);
		}
		else if (dir.x > 0 && m_Trans->GetWorldScale().x < 0)
		{
			m_Trans->SetLocalScale(1.0f, 1.0f, 1.0f);
		}

		ChangeState(PLAYER_IDLE);
	}

	HitInfo info;
	info.Damage = 10.0f;
	info.ForceVec = Vector3f(200.0f, 0.0f, 0.0f);
	info.ForceVec.x *= m_Trans->GetWorldScale().x;
	info.HitStunTime = 1.0f;
	info.state = HitState::HS_KNOCKBACK;


	AttackProcess(info);


	Vector3f dir = InputMoveFunction();
	dir.Normalize();

	Vector3f movePos = dir * (m_WalkSpeed)* TimeManager::GetDeltaTime();
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

void Player::Attack01State()
{
	if (Parts->IsCurAniName(L"Attack01") && Parts->IsAniEnd())
	{
		ChangeState(PlayerState::PLAYER_IDLE);
	}
	if (InputManager::IsDown(L"X") && Parts->IsCurAniName(L"Attack01") && Parts->CurAniPer() > 0.4f)
	{
		Vector3f dir = InputMoveFunction();
		Vector3f focDir;
		if (m_Trans->GetWorldScale().x * dir.x > 0.0f)
		{
			focDir.x = m_Trans->GetWorldScale().x * 100.0f;
		}
		else if (m_Trans->GetWorldScale().x * dir.x == 0.0f)
		{
			focDir.x = m_Trans->GetWorldScale().x * 60.0f;
		}
		AddForce(focDir);
		ChangeState(PlayerState::PLAYER_Attack02);
	}
	HitInfo info;
	info.Damage = 10.0f;
	info.ForceVec = Vector3f(100.0f, 0.0f, 0.0f);
	info.ForceVec.x *= m_Trans->GetWorldScale().x;
	info.HitStunTime = 1.0f;
	info.state = HitState::HS_KNOCKBACK;

	AttackProcess(info);
}

void Player::Attack02State()
{

	if (Parts->IsCurAniName(L"Attack02") && Parts->IsAniEnd())
	{
		ChangeState(PlayerState::PLAYER_IDLE);
	}
	if (InputManager::IsDown(L"X") && Parts->IsCurAniName(L"Attack02") && Parts->CurAniPer() > 0.4f)
	{
		Vector3f dir = InputMoveFunction();
		Vector3f focDir;
		if (m_Trans->GetWorldScale().x * dir.x > 0.0f)
		{
			focDir.x = m_Trans->GetWorldScale().x * 100.0f;
		}
		else if (m_Trans->GetWorldScale().x * dir.x == 0.0f)
		{
			focDir.x = m_Trans->GetWorldScale().x * 60.0f;
		}
		AddForce(focDir);
		ChangeState(PlayerState::PLAYER_Attack04);
	}
	HitInfo info;
	info.Damage = 10.0f +RandomInt(-2, 2);
	info.ForceVec = Vector3f(100.0f, 0.0f, 0.0f);
	info.ForceVec.x *= m_Trans->GetWorldScale().x;
	info.HitStunTime = 1.0f;
	info.state = HitState::HS_KNOCKBACK;

	AttackProcess(info);
}

void Player::Attack04State()
{
	if (Parts->IsCurAniName(L"Attack04") && Parts->IsAniEnd())
	{
		ChangeState(PlayerState::PLAYER_IDLE);
	}
	HitInfo info;
	info.Damage = 10.0f + RandomInt(-2, 2);
	info.ForceVec = Vector3f(100.0f, 0.0f, 600.0f);
	info.ForceVec.x *= m_Trans->GetWorldScale().x;
	info.HitStunTime = 1.0f;
	info.state = HitState::HS_AIRBORNE;

	AttackProcess(info);
}

void Player::Attack08State()
{
	if (Parts->IsCurAniName(L"Attack08") && Parts->IsAniEnd())
	{
		ChangeState(PlayerState::PLAYER_IDLE);
	}
	HitInfo info;
	info.Damage = 10.0f + RandomInt(-2, 2);
	info.ForceVec = Vector3f(200.0f, 0.0f, 0.0f);
	info.ForceVec.x *= m_Trans->GetWorldScale().x;
	info.HitStunTime = 1.0f;
	info.state = HitState::HS_KNOCKBACK;

	AttackProcess(info);
}

void Player::HitState()
{
	if (m_Force.Length() < 1.0f && StunWaiting.Check())
	{
		ChangeState(PLAYER_IDLE);
	}
}

void Player::AirHitState()
{
	if (m_bGorund && m_Force.z <= 0.0f)
	{
		ChangeState(PLAYER_DOWN);
	}
}

void Player::DownState()
{
	if (StunWaiting.Check())
	{
		ChangeState(PLAYER_IDLE);
	}
}

void Player::Skill01State()
{
	if (m_Effect->IsAniEnd())
	{
		m_Effect->DeleteAllPart();
	}
	if (Parts->CurAniPer()> 0.25f)
	{
		m_Effect->AniOn();
	}
	if (Parts->IsCurAniName(L"Attack05") && Parts->IsAniEnd())
	{
		ChangeState(PlayerState::PLAYER_IDLE);
	}
	HitInfo info;
	info.Damage = 20.0f + RandomInt(-3, 3);
	info.ForceVec = Vector3f(100.0f, 0.0f, 800.0f);
	info.ForceVec.x *= m_Trans->GetWorldScale().x;
	info.HitStunTime = 1.0f;
	info.state = HitState::HS_AIRBORNE;

	AttackProcess(info);
}

void Player::Skill02State()
{
	if (m_Effect->IsAniEnd())
	{
		m_Effect->DeleteAllPart();
	}
	if (Parts->IsCurAniName(L"Attack13") && Parts->IsAniEnd())
	{
		ChangeState(PlayerState::PLAYER_IDLE);
	}
	if (Parts->IsCurAniName(L"Attack12") && Parts->IsAniEnd())
	{
		ChangeAni(L"Attack13");
		m_Effect->AniOn();
	}
	HitInfo info;
	info.Damage = 60.0f + RandomInt(-3, 3);
	info.ForceVec = Vector3f(800.0f, 0.0f, 600.0f);
	info.ForceVec.x *= m_Trans->GetWorldScale().x;
	info.HitStunTime = 1.0f;
	info.state = HitState::HS_AIRBORNE;

	AttackProcess(info);

}

void Player::DeadState()
{
	HitCol->SetUpdate(false);

	if (m_bGorund == false)
	{
		if (Parts->IsCurAniName(L"AirHit") == false)
		{
			Parts->ChangeAni(L"AirHit");
		}
		return;
	}

	if (Parts->IsCurAniName(L"Down") == false)
	{
		Parts->ChangeAni(L"Down");
	}
	if (FadeStartWating.Check())
	{
		if(m_Fade !=nullptr)
			m_Fade->FadeOut();
	}
	// 데드시간 체크.
	if (!DeadTime.Check())
	{
		return;
	}
	// 데드시간이 지나면 세리아 룸에서 부활.
	GetActor()->GetLevel()->ChangeLevel(L"SeriaRoom");
	// 상태 초기화.
	m_CurHP = m_MaxHP;
	m_CurMP = m_MaxMP;
	m_VirPos = Vector3f(0.0f, -196.0f, 0.0f);
	HitCol->SetUpdate(true);
	m_bBattle = false;
	ChangeState(PLAYER_IDLE);
}

bool Player::IsSkill()
{
	return PLAYER_Skill01 <= m_State && PLAYER_MAX > m_State;
}

bool Player::IsHit()
{
	return m_State == PLAYER_HIT || m_State == PLAYER_AIRHIT || m_State == PLAYER_DOWN;
}
