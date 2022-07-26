#include "Player.h"

#include<Camera.h>
#include<Col2DRect.h>

#include"BackGround.h"
#include"DamageNumber.h"
#include<TileMapRender.h>
#include<MyRandom.h>
#include<DxDebug.h>
#include<Level.h>
#include"Fade.h"
bool Player::Init()
{
	BattlePawn::Init();

	// Move Stete Setting.
	m_VirPos = Vector3f();
	m_WalkSpeed = 200.0f;
	m_RunSpeed = 300.0f;
	m_JumpPower = 550.0f;
	m_Gravity = -980.0f;

	// Game State Setting.
	m_CurHP = m_MaxHP = 100.0f;
	m_CurMP = m_MaxMP = 100.0f;

	// Transform Setting.
	m_Trans->SetLocalScale(1.0f, 1.0f, 1.0f);
	m_VirPos = Vector3f(0.0f, -196.0f, 0.0f);

	// Animaiton.
	PartSetting();
	ChangeAni(L"Idle");
	
	// Effect
	m_Effect = AddComponent<RenderParts>();

	// Col - Hit
	HitCol = AddComponent<Col2DRect>(L"PlayerHit");
	HitCol->SetLocalSubScale(Vector3f(64.0f, 124.0f, 1.0f));
	HitColPos = (Vector3f(0.0f, 62.0f, 1.0f));

	// Col - Attack
	AttackCol = AddComponent<Col2DRect>(L"PlayerAttack");
	AttackCol->PushEnterFunc(&Player::AttackEnter, this);
	AttackCol->PushStayFunc(&Player::AttackStay, this);
	AttackCol->PushExitFunc(&Player::AttackExit, this);

	// Col - Restrict movement
	MoveCol = AddComponent<Col2DRect>(L"PlayerMove");
	MoveCol->SetLocalSubScale(Vector3f(10.0f, 10.0f, 1.0f));

	// Sound.
	m_BackSound= AddComponent<MySoundPlayer>();
	m_WeaponSound = AddComponent<MySoundPlayer>();
	//Timer.
	float SetDeadTime = 5.0f;
	DeadTime.SetTime(SetDeadTime);
	FadeStartWating.SetTime(SetDeadTime - 1.0f);

	m_hairNumber = 0;
	m_coatNumber = 0;
	m_pantsNumber = 0;

	return true;
}

void Player::Update()
{
	BattlePawn::Update();
	if (m_bInputStop == true)
	{
		return;
	}
	if (IsDead())
	{
		if (m_State != PLAYER_DEAD)
			ChangeState(PLAYER_DEAD);
		return;
	}
	if (m_bGorund)
	{
		if (InputManager::IsDown(L"S") && !IsSkill() && !IsHit())
		{
			if (m_CurMP - 5.0f > 0)
			{
				ChangeState(PLAYER_Skill01);
				m_CurMP -= 5.0f;
			}
			else
			{
				SoundPlay(13);
			}
		}
		if (InputManager::IsDown(L"Z") && !IsSkill() && !IsHit())
		{
			if (m_CurMP - 30.0f > 0)
			{
				ChangeState(PLAYER_Skill02);
				m_CurMP -= 30.0f;
			}
			else
			{
				SoundPlay(13);
			}
		}
	}
	if (InputManager::IsPressed(L"Q"))
	{
		HitInfo info;
		info.Damage = 1.0f;
		DamageProcess(info);
	}
	if (InputManager::IsPressed(L"W"))
	{
		m_CurHP = 100.0f;
	}
	if (InputManager::IsPressed(L"E"))
	{
		m_CurMP = 100.0f;
	}
	if (InputManager::IsDown(L"1"))
	{
		switch ((++m_hairNumber) % 3)
		{
		case 0:
			Parts->SettingPart(RenderParts::RP_Hair, L"sm_hair0000a.png", L"sm_hair0000a.data");
			break;
		case 1:
			Parts->SettingPart(RenderParts::RP_Hair, L"sm_hair10000a.png", L"sm_hair10000a.data");
			break;
		case 2:
			Parts->SettingPart(RenderParts::RP_Hair, L"sm_hair11500a.png", L"sm_hair11500a.data");
			break;
		default:
			break;
		}
	}
	if (InputManager::IsDown(L"2"))
	{
		switch ((++m_coatNumber) % 3)
		{
		case 0:
			Parts->SettingPart(RenderParts::RP_Coat, L"sm_coat0000a.png", L"sm_coat0000a.data");
			break;
		case 1:
			Parts->SettingPart(RenderParts::RP_Coat, L"sm_coat0200a_p1.png", L"sm_coat0200a.data");
			break;
		case 2:
			Parts->SettingPart(RenderParts::RP_Coat, L"sm_coat0200a_p2.png", L"sm_coat0200a.data");
			break;
		default:
			break;
		}
	}
	if (InputManager::IsDown(L"3"))
	{
		switch ((++m_coatNumber) % 4)
		{
		case 0:
			Parts->SettingPart(RenderParts::RP_PantsA, L"sm_pants0000a.png", L"sm_pants0000a.data");
			Parts->SettingPart(RenderParts::RP_PantsB, L"sm_pants0000b.png", L"sm_pants0000b.data");
			break;
		case 1:
			Parts->SettingPart(RenderParts::RP_PantsA, L"sm_pants0200a.png", L"sm_pants0200a.data");
			Parts->SettingPart(RenderParts::RP_PantsB, L"sm_pants0200b.png", L"sm_pants0200b.data");
			break;
		case 2:
			Parts->SettingPart(RenderParts::RP_PantsA, L"sm_pants0201a.png", L"sm_pants0200a.data");
			Parts->SettingPart(RenderParts::RP_PantsB, L"sm_pants0201b.png", L"sm_pants0200b.data");
			break;
		case 3:
			Parts->SettingPart(RenderParts::RP_PantsA, L"sm_pants0202a.png", L"sm_pants0200a.data");
			Parts->SettingPart(RenderParts::RP_PantsB, L"sm_pants0202b.png", L"sm_pants0200b.data");
			break;
		default:
			break;
		}
	}
}

void Player::LateUpdate()
{
	BattlePawn::LateUpdate();
	CameraCheck();
}

void Player::DebugRender()
{
	DxDebug::DrawRect(GetTransform()->GetWorldPosition(), Vector3f(100.0f,1.0f,1.0f), Color4f(1.0f,0.0f,0.0f), GetTransform()->GetWorldRotate().z);
	DxDebug::DrawRect(GetTransform()->GetWorldPosition(), Vector3f(1.0f, 100.0f, 1.0f), Color4f(0.0f, 1.0f, 0.0f), GetTransform()->GetWorldRotate().z);
}


void Player::CameraCheck()
{
	if (m_Camera != nullptr)
	{
		FRect CamRect;
		CamRect.Position = Vector2f(m_VirPos.x, m_VirPos.y);
		CamRect.Size = m_Camera->GetOrthSize();
		
		FRect BackRect;
		BackRect.Position = m_Backgorund->GetTransform()->GetWorld2DPosition();
		BackRect.Size = m_Backgorund->GetTransform()->GetWorld2DScale();

		Vector3f CalCameraPos;
		CalCameraPos.x = CamRect.Position.x;
		CalCameraPos.y = CamRect.Position.y;
		CalCameraPos.z = m_Camera->GetTransform()->GetWorldPosition().z;

		if (CamRect.Bottom() <= BackRect.Bottom())
		{
			CalCameraPos.y += BackRect.Bottom() - CamRect.Bottom();
		}
		if (CamRect.Top() >= BackRect.Top())
		{
			CalCameraPos.y -= CamRect.Top() - BackRect.Top();
		}
		if (CamRect.Left() < BackRect.Left())
		{
			CalCameraPos.x += BackRect.Left() - CamRect.Left();
		}
		if (CamRect.Right() > BackRect.Right())
		{
			CalCameraPos.x -= CamRect.Right() - BackRect.Right();
		}

		m_Camera->GetTransform()->SetWorldPosition(CalCameraPos);
	}
}

void Player::SetCamera(SPTR<Camera> cam)
{
		m_Camera = cam;
}
void Player::VirPosUpdate()
{
	BattlePawn::VirPosUpdate();
	MoveCol->SetWorldSubPosition(Vector3f(m_VirPos.x, m_VirPos.y, 0.0f));
}

void Player::Jump()
{
	if(m_bGorund)
		AddForce(Vector3f(0.0f, 0.0f, m_JumpPower));
}

void Player::AttackEnter(ComCol * my, ComCol * other)
{
	BattlePawn::AttackEnter(my, other);
}

void Player::AttackStay(ComCol * my, ComCol * other)
{
	BattlePawn::AttackStay(my, other);
}

void Player::AttackExit(ComCol * my, ComCol * other)
{
	BattlePawn::AttackExit(my, other);
}

Vector3f Player::InputMoveFunction()
{

	Vector3f dir = Vector3f();

	if (InputManager::IsPressed(L"LEFT"))
	{
		dir.x -= 1.0f;
	}
	if (InputManager::IsPressed(L"RIGHT"))
	{
		dir.x += 1.0f;
	}
	if (InputManager::IsPressed(L"UP"))
	{
		dir.y += 1.0f;
	}
	if (InputManager::IsPressed(L"DOWN"))
	{
		dir.y -= 1.0f;
	}
	return dir;
}

void Player::PartSetting()
{
	Parts->SettingPart(RenderParts::RP_Skin, L"Character_Swordman.png", L"skin.data");
	Parts->SettingPart(RenderParts::RP_ShoesA, L"sm_shoes0000a.png", L"sm_shoes0000a.data");
	Parts->SettingPart(RenderParts::RP_ShoesB, L"sm_shoes0000b.png", L"sm_shoes0000b.data");
	Parts->SettingPart(RenderParts::RP_PantsA, L"sm_pants0000a.png", L"sm_pants0000a.data");
	Parts->SettingPart(RenderParts::RP_PantsB, L"sm_pants0000b.png", L"sm_pants0000b.data");
	Parts->SettingPart(RenderParts::RP_Coat, L"sm_coat0000a.png", L"sm_coat0000a.data");
	Parts->SettingPart(RenderParts::RP_Hair, L"sm_hair0000a.png", L"sm_hair0000a.data");
	Parts->SettingPart(RenderParts::RP_WeaponA, L"lswd0000b.png", L"lswdB.data");
	Parts->SettingPart(RenderParts::RP_WeaponB, L"lswd0000c.png", L"lswdC.data");
	AniLoad(L"Character_Swordman.data");
}
void Player::SoundPlay(size_t SoundNumber)
{
	switch (SoundNumber)
	{
	case 0:
		m_Sound->Play(L"sm_atk_01.ogg");
		break;
	case 1:
		m_Sound->Play(L"sm_atk_02.ogg");
		break;
	case 2:
		m_Sound->Play(L"sm_atk_03.ogg");
		break;
	case 3:
		m_Sound->Play(L"sm_jump.ogg");
		break;
	case 4:
		m_Sound->Play(L"sm_jumpatk_01.ogg");
		break;
	case 5:
		m_Sound->Play(L"sm_jumpatk_02.ogg");
		break;
	case 6:
		m_Sound->Play(L"sm_upslash.ogg");
		break;
	case 7:
		m_Sound->Play(L"sm_gue_01.ogg");
		break;
	case 8:
		m_Sound->Play(L"sm_gue_02.ogg");
		break;
	case 9 :
		m_Sound->Play(L"sm_die.ogg");
		break;
	case 10:
		m_Sound->Play(L"sm_dmg_01.ogg");
		break;
	case 11:
		m_Sound->Play(L"sm_dmg_02.ogg");
		break;
	case 12:
		m_Sound->Play(L"sm_dmg_03.ogg");
		break;
	case 13:
		m_Sound->Play(L"sm_nomana.ogg");
		break;

	default:
		break;
	}
}
void Player::WeaponSound(size_t number)
{
	switch (number)
	{
	case 0:
		m_WeaponSound->Play(L"sqrswda_01.ogg");
		break;
	case 1:
		m_WeaponSound->Play(L"sqrswda_02.ogg");
		break;
	case 2:
		m_WeaponSound->Play(L"sqrswda_hit_01.ogg");
		break;
	case 3:
		m_WeaponSound->Play(L"sqrswda_hit_02.ogg");
		break;
	default:
		break;
	}
}
void Player::SetBackSound(std::wstring _Sound, int flag)
{
	if (m_BackSoundName == _Sound && flag != 1)
	{
		return;
	}
	m_BackSoundName = _Sound;
	m_BackSound->Stop();
	m_BackSound->Play(m_BackSoundName.c_str(), true);
}
void Player::TimerSet()
{
}

void Player::EventDataClear()
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

void Player::AttackProcess(const HitInfo & info)
{
	std::list<AttListInfo>::iterator itStart = AttList.begin();
	std::list<AttListInfo>::iterator itEnd = AttList.end();
	for (; itStart != itEnd; ++itStart)
	{
		if ((*itStart).isHit == false)
		{
			(*itStart).m_AttackTaget->DamageProcess(info);
			(*itStart).isHit = true;
			WeaponSound(RandomInt(2, 3));
		}
	}
}

void Player::DamageProcess(HitInfo info)
{
	m_CurHP -= info.Damage;
	m_CurHP = m_CurHP < 0.0f ? 0.0f : m_CurHP;
	AddForce(info.ForceVec);
	StunWaiting.SetTime(info.HitStunTime);
	StunWaiting.Reset();

	switch (info.state)
	{
	case BattlePawn::HS_KNOCKBACK:
		if (m_State != PLAYER_AIRHIT && m_State != PLAYER_DOWN && m_bGorund)
			ChangeState(PLAYER_HIT);
		else
		{
			if (m_State == PLAYER_DOWN)
			{
				AddForce(Vector3f(0.0f, 0.0f, fabsf(info.ForceVec.x)));
			}
			else
			{
				AddForce(Vector3f(0.0f, 0.0f, fabsf(info.ForceVec.x) * (500.0f / fabsf(info.ForceVec.x))));
			}
			ChangeState(PLAYER_AIRHIT);
		}
		break;
	case BattlePawn::HS_THROWKNOCKBACK:
		ChangeState(PLAYER_AIRHIT);
		break;
	case BattlePawn::HS_AIRBORNE:
		ChangeState(PLAYER_AIRHIT);
		break;
	case BattlePawn::HS_MAX:
		break;
	default:
		break;
	}
	SPTR<Actor> ptr = GetActor()->GetLevel()->CreateActor(0);
	ptr->GetTransform()->SetWorldPosition(m_Trans->GetWorldPosition() + Vector3f(-55.0f, 80.0f, -10.0f) + Vector3f((float)RandomInt(-30,30), (float)RandomInt(-30, 30),0.0f));
	SPTR<DamageNumber> comPtr = ptr->AddComponent<DamageNumber>();
	comPtr->InitSetting(4, L"DamageFont.png", (int)info.Damage);
	comPtr->SetVelocity(Vector3f(0.0f, 100.0f, 0.0f));

	SoundPlay(RandomInt(10, 12));
}

void Player::SetFade(SPTR<Fade> fade)
{
	m_Fade = fade;
}

Player::Player() : m_State(PLAYER_IDLE), m_bBattle(false) , m_bInputStop(false)
{
}


Player::~Player()
{
}
