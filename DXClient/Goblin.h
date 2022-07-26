#pragma once
#include "Monster.h"
class Goblin : public Monster
{
private:
	enum GoblinState
	{
		GS_IDLE,
		GS_WALK,
		GS_ATTACK,
		GS_HIT,
		GS_AIRHIT,
		GS_DOWN,
		GS_STEND,
		GS_DEAD,
		GS_MAX
	};
private:
	GoblinState m_State;
	float MoveDirX;
private:
	Timehelper WalkRandomCool;
	Timehelper IdleWaiting;
	Timehelper WalkWaiting;
	Timehelper StandWaiting;
	Timehelper DeadWaiting;
public:
	bool Init() override;
	void Update() override;
	void DebugRender() override;
protected:
	void FSMUpdate() override;
	void ChangeState(GoblinState newState);
	void IdleState();
	void WalkState();
	void AttackState();
	void HitState();
	void AirHitState();
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
	Goblin();
	~Goblin();
};

