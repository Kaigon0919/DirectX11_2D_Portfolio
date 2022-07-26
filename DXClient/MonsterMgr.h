#pragma once
#include <Component.h>
#include<list>

class Player;
class Monster;
class MonsterMgr : public Component
{
public:
	enum MonType
	{
		MT_GOBLIN0,
		MT_GOBLIN1,
		MT_TAU,
		MT_MAX
	};
private:
	std::list<SPTR<Monster>> m_Monster;
public:
	void CreateMonster(MonType type, Vector2f Pos);
	void LoadMonBat(const wchar_t* BatFile);
	void SetBackground(Actor * back);
// player info.
private:
	SPTR<Player> m_Player;
public:
	void SetPlayer(SPTR<Player> player);
	bool MonAllDeath();
public:
	MonsterMgr();
	~MonsterMgr();
};

