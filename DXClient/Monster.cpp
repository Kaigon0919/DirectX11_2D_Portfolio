#include "Monster.h"

#include<Com2DFrameAni.h>
#include<Render2DSprite.h>
#include<Col2DRect.h>
#include<SaveAndLoadData.h>
#include<BRStream.h>
#include<RenderParts.h>
#include<DxDebug.h>
#include<Level.h>

bool Monster::Init()
{
	BattlePawn::Init();

	SPTR<Transform> trans = GetComponent<Transform>();
	trans->SetLocalScale(1.0f, 1.0f, 1.0f);

	GetActor()->GetLevel()->CMgr.ColLink(L"PlayerAttack", L"MonsterHit");
	GetActor()->GetLevel()->CMgr.ColLink(L"MonsterAttack", L"PlayerHit");

	// Col.
	AttackCol = AddComponent<Col2DRect>(L"MonsterAttack");
	AttackCol->PushEnterFunc(&Monster::AttackEnter, this);
	AttackCol->PushStayFunc(&Monster::AttackStay, this);
	AttackCol->PushExitFunc(&Monster::AttackExit, this);
	AttackCol->SetUpdate(false);

	HitCol = AddComponent<Col2DRect>(L"MonsterHit");
	HitCol->PushEnterFunc(&Monster::HitEnter, this);
	HitCol->PushStayFunc(&Monster::HitStay, this);
	HitCol->PushExitFunc(&Monster::HitExit, this);

	return true;
}

void Monster::Update()
{
	BattlePawn::Update();
}

void Monster::DebugRender()
{
	DxDebug::DrawRect(GetTransform()->GetWorldPosition(), Vector3f(100.0f, 1.0f, 1.0f), Color4f(1.0f, 0.0f, 0.0f), GetTransform()->GetWorldRotate().z);
	DxDebug::DrawRect(GetTransform()->GetWorldPosition(), Vector3f(1.0f, 100.0f, 1.0f), Color4f(0.0f, 1.0f, 0.0f), GetTransform()->GetWorldRotate().z);
}

void Monster::SetPlayer(Player * player)
{
	m_Player = player;
}

Monster::Monster()
{
}


Monster::~Monster()
{
}
