#pragma once
#include"BattlePawn.h"
#include"Player.h"
#include"DamageNumber.h"

class Player;
class Monster : public BattlePawn
{
protected:
	SPTR<Player> m_Player;
public:
	bool Init() override;
	void Update() override;
	void DebugRender() override;
protected:
	virtual void AttackEnter(ComCol * thisCol, ComCol * OtherCol) {}
	virtual void AttackStay(ComCol * thisCol, ComCol * OtherCol) {}
	virtual void AttackExit(ComCol * thisCol, ComCol * OtherCol) {}
	virtual void HitEnter(ComCol * thisCol, ComCol * OtherCol) {}
	virtual void HitStay(ComCol * thisCol, ComCol * OtherCol) {}
	virtual void HitExit(ComCol * thisCol, ComCol * OtherCol) {}
public:
	void SetPlayer(Player * player);
public:
	Monster();
	~Monster();
};

