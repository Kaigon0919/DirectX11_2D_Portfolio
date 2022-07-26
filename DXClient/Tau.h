#pragma once
#include "Monster.h"
class Tau :	public Monster
{
private:
	enum TauState
	{
		TS_IDLE,
		TS_WALK,
		TS_ATTACK,
		TS_HIT,
		TS_AIRHIT,
		TS_DOWN,
		TS_ROAR,
		TS_RUSH,
		TS_STEND,
		TS_DEAD,
		TS_MAX
	};
private:
	TauState m_State;
	float m_RushSpeed;
	float MoveDirX;
private:
	Timehelper WalkRandomCool;
	Timehelper IdleWaiting;
	Timehelper WalkWaiting;
	Timehelper StandWaiting;
	Timehelper DeadWaiting;
	Timehelper SuperArmorTime;
private:
	int SACount;
	bool m_bSuperArmor;
public:
	bool Init() override;
	void Update() override;
	void DebugRender() override;
protected:
	void FSMUpdate() override;
	void ChangeState(TauState newState);
	void IdleState();
	void WalkState();
	void AttackState();
	void HitState();
	void AirHitState();
	void RoarState();
	void RushState();
	void DownState();
	void StendState();
	void DeadState();
private:
	void AttackEnter(ComCol * thisCol, ComCol * OtherCol)override;
	void AttackStay(ComCol * thisCol, ComCol * OtherCol)override;
	void AttackExit(ComCol * thisCol, ComCol * OtherCol) override;
	void HitEnter(ComCol * thisCol, ComCol * OtherCol) override;
	void HitStay(ComCol * thisCol, ComCol * OtherCol) override;
	void HitExit(ComCol * thisCol, ComCol * OtherCol)override;

	void DamageProcess(HitInfo info) override;
private:
	void SoundPlay(size_t number);
public:
	Tau();
	~Tau();
};

