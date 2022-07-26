#pragma once
#include<ComScript.h>

#include"BattlePawn.h"
class Camera;
class ComCol;
class Fade;
class Col2DRect;
class Com2DFrameAni;
class MySoundPlayer;
class Player : public BattlePawn
{
private:
	enum PlayerState
	{
		PLAYER_IDLE,
		PLAYER_BATTLEIDLE,
		PLAYER_WALK,
		PLAYER_RUN,
		PLAYER_JUMP,
		PLAYER_JUMPATTACK,
		PLAYER_Attack01,
		PLAYER_Attack02,
		PLAYER_Attack04,
		PLAYER_Attack08,
		PLAYER_HIT,
		PLAYER_AIRHIT,
		PLAYER_DOWN,
		PLAYER_Skill01,
		PLAYER_Skill02,
		PLAYER_DEAD,
		PLAYER_MAX
	};
	struct AttackInfo
	{
		float Damage;
		Vector3f hitValue;
		BattlePawn::HitState hitState;
	};
// Player State.
private:
	float m_RunSpeed;
	float m_JumpVelocity;
	float m_JumpPower;
	bool m_bBattle;
	bool m_bInputStop;
	unsigned int m_hairNumber;
	unsigned int m_coatNumber;
	unsigned int m_pantsNumber;
private:
	float m_MaxMP;
	float m_CurMP;
public:
	void SetBattle(bool isBattle)
	{
		m_bBattle = isBattle;
	}
	float GetCurHP()const
	{
		return m_CurHP;
	}
	float GetMaxHP()const
	{
		return m_MaxHP;
	}
	float GetCurMP()const
	{
		return m_CurMP;
	}
	float GetMaxMP()const
	{
		return m_MaxMP;
	}
	void AddHP(float value)
	{
		m_CurHP += value;
		if (m_CurHP < 0) m_CurHP = 0.0f;
		if (m_CurHP > m_MaxHP) m_CurHP = m_MaxHP;
	}
	void AddMP(float value)
	{
		m_CurMP += value;
		if (m_CurMP < 0) m_CurMP = 0.0f;
		if (m_CurMP > m_MaxMP) m_CurMP = m_MaxMP;
	}
	void SetInputStop(bool isStop)
	{
		m_bInputStop = isStop;
	}
// Camera.
private:
	SPTR<Camera> m_Camera;
public:
	void CameraCheck();
public:
	void SetCamera(SPTR<Camera> cam);

// Transform.
private:
	void VirPosUpdate() override;
	void Jump();

// Update.
public:
	bool Init() override;
	void Update() override;
	void LateUpdate() override;
	void DebugRender() override;
// Col Function.
private:
	SPTR<Col2DRect> MoveCol;
private:
	void AttackEnter(ComCol*, ComCol*);
	void AttackStay(ComCol*, ComCol*);
	void AttackExit(ComCol*, ComCol*);

// Input.
private:
	Vector3f InputMoveFunction();

// FSM.
private:
	PlayerState m_State;
private:
	void FSMUpdate() override;
	void ChangeState(PlayerState newState);
private:
	void IdleState();
	void BattleState();
	void WalkState();
	void RunState();
	void JumpState();
	void JumpAttackState();
	void Attack01State();
	void Attack02State();
	void Attack04State();
	void Attack08State();
	void HitState();
	void AirHitState();
	void DownState();
	void Skill01State();
	void Skill02State();
	void DeadState();

	bool IsSkill();
	bool IsHit();
// Animation.
private:
	void PartSetting();
// Sound.
private:
	SPTR<MySoundPlayer> m_BackSound;
	std::wstring m_BackSoundName;
	SPTR<MySoundPlayer> m_WeaponSound;
private:
	void SoundPlay(size_t SoundNumber);
	void WeaponSound(size_t number);
public:
	void SetBackSound(std::wstring _Sound, int flag = 0);
//Timer.
private:
	float RunWaitingTime;
	void TimerSet();

	Timehelper DeadTime;

// Other.
private:
	SPTR<RenderParts> m_Effect;
	SPTR<Fade> m_Fade;
	Timehelper FadeStartWating;
private:
	void EventDataClear();
	void AttackProcess(const HitInfo& info);
	void DamageProcess(HitInfo info) override;
public:
	void SetFade(SPTR<Fade> fade);
public:
	Player();
	~Player();
};