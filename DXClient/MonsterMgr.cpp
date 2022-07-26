#include "MonsterMgr.h"

#include<PathManager.h>
#include<BRStream.h>
#include<SaveAndLoadData.h>
#include<RenderParts.h>
#include<Level.h>
#include"Goblin.h"
#include"Tau.h"



void MonsterMgr::CreateMonster(MonType type, Vector2f Pos)
{
	SPTR<Actor> actor = GetActor()->GetLevel()->CreateActor(0,L"Monster");
	SPTR<Monster> mon;
	SPTR<RenderParts> Part;
	switch (type)
	{
	case 0:
		mon = actor->AddComponent<Goblin>();
		mon->SetVirtualPosition(Vector3f(Pos.x, Pos.y, 0.0f));
		Part = actor->GetComponent<RenderParts>();
		Part->SettingPart(RenderParts::RP_Skin, L"GoblinBody0.png", L"GoblinBody0.data");
		mon->AniLoad(L"goblin0.data");
		break;
	case 1:
		mon = actor->AddComponent<Goblin>();
		mon->SetVirtualPosition(Vector3f(Pos.x, Pos.y, 0.0f));
		Part = actor->GetComponent<RenderParts>();
		Part->SettingPart(RenderParts::RP_Skin, L"GoblinBody1.png", L"GoblinBody1.data");
		Part->SettingPart(RenderParts::RP_WeaponA, L"GoblinWeapon1.png", L"GoblinWeapon1.data");
		mon->AniLoad(L"goblin1.data");
		break;
	case 2:
		mon = actor->AddComponent<Tau>();
		mon->SetVirtualPosition(Vector3f(Pos.x, Pos.y, 0.0f));
		Part = actor->GetComponent<RenderParts>();
		Part->SettingPart(RenderParts::RP_Skin, L"Tau.png", L"Tau.data");
		mon->AniLoad(L"Tau.data");
		break;
	}
	mon->SetPlayer(m_Player.Get());
	m_Monster.push_back(mon);
}

void MonsterMgr::LoadMonBat(const wchar_t * BatFile)
{
	std::wstring Path = PathManager::FindPath(L"MonsterBat") + BatFile;

	BRStream Stream = BRStream(Path.c_str());

	int size;
	Stream.Read(size);
	MonData data;
	for (int i = 0; i < size; ++i)
	{
		Stream.Read(data);
		CreateMonster((MonType)data.MonType, data.Pos);
	}
}

void MonsterMgr::SetBackground(Actor * back)
{
	std::list<SPTR<Monster>>::iterator itStart = m_Monster.begin();
	std::list<SPTR<Monster>>::iterator itEnd = m_Monster.end();
	for (; itStart != itEnd; ++itStart)
	{
		(*itStart)->SetBackground(back);
	}
}

void MonsterMgr::SetPlayer(SPTR<Player> player)
{
	m_Player = player;
	std::list<SPTR<Monster>>::iterator itStart = m_Monster.begin();
	std::list<SPTR<Monster>>::iterator itEnd = m_Monster.end();
	for (; itStart != itEnd; ++itStart)
	{
		(*itStart)->SetPlayer(m_Player.Get());
	}
}

bool MonsterMgr::MonAllDeath()
{
	std::list<SPTR<Monster>>::iterator itStart = m_Monster.begin();
	std::list<SPTR<Monster>>::iterator itEnd = m_Monster.end();
	for (; itStart != itEnd; ++itStart)
	{
		if ((*itStart)->IsDead() == false)
		{
			return false;
		}
	}
	return true;
}

MonsterMgr::MonsterMgr()
{
}


MonsterMgr::~MonsterMgr()
{
}
