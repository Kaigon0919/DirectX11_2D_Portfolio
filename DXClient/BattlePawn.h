#pragma once
#include<ComScript.h>
#include<RenderParts.h>
#include<MySoundPlayer.h>
#include<SaveAndLoadData.h>
#include<Col2DRect.h>
#include"Timehelper.h"
class BackGround;
class TileMapRender;
class BattlePawn : public ComScript
{
protected:
	enum HitState
	{
		HS_KNOCKBACK,
		HS_THROWKNOCKBACK,
		HS_AIRBORNE,
		HS_MAX
	};
	struct HitInfo
	{
		HitState state;
		Vector3f ForceVec;
		float Damage;
		float HitStunTime;
	};
protected:
	float m_WalkSpeed;

	float m_MaxHP;
	float m_CurHP;

	bool m_bGorund;
	Vector3f m_Force;
	float m_Gravity;
// Update.
public:
	bool Init() override;
	void Update() override;
	void LateUpdate() override;

// Transform.
protected:
	SPTR<Transform> m_Trans;
	Vector3f m_VirPos;
public:
	void VirMove(float x, float y, float z);
	void VirMove(const Vector3f& velue);
	Vector3f GetVirtualPosition()const {
		return m_VirPos;
	}
	void SetVirtualPosition(const Vector3f& velue)
	{
		m_VirPos = velue;
	}
	void AddForce(const Vector3f& vec)
	{
		m_Force += vec;
	}
	void SetForce(const Vector3f& vec)
	{
		m_Force = vec;
	}
protected:
	virtual void VirPosUpdate();
// Animation
protected:
	SPTR<RenderParts> Parts;
	std::list<AniEventData*> EventDataList;
	void ChangeAni(const wchar_t* AniName);
public:
	void EventOn(void* Data);
	void EventOff(void* Data);
private:
	void EventDataClear();
public:
	void AniLoad(const wchar_t * AniData);
// Col.
protected:
	SPTR<Col2DRect> AttackCol;
	SPTR<Col2DRect> HitCol;
	Vector3f AttackColPos;
	Vector3f HitColPos;
protected:
	virtual void AttackEnter(ComCol * thisCol, ComCol * OtherCol);
	virtual void AttackStay(ComCol * thisCol, ComCol * OtherCol);
	virtual void AttackExit(ComCol * thisCol, ComCol * OtherCol);
	virtual void HitEnter(ComCol * thisCol, ComCol * OtherCol) {}
	virtual void HitStay(ComCol * thisCol, ComCol * OtherCol) {}
	virtual void HitExit(ComCol * thisCol, ComCol * OtherCol) {}
// FSM.
protected:
	virtual void FSMUpdate() = 0;
public:
	virtual bool IsDead()
	{
		return m_CurHP <= 0.0f;
	}
// Backgorund.
protected:
	SPTR<BackGround> m_Backgorund;
	SPTR<TileMapRender> m_TileMap;
public:
	virtual void SetBackground(Actor * back);
// Sound.
	SPTR<MySoundPlayer> m_Sound;

// Other.
	virtual void DamageProcess(HitInfo info);
	Timehelper StunWaiting;
protected:
	struct AttListInfo
	{
		BattlePawn* m_AttackTaget;
		bool isHit;
	};
	std::list<AttListInfo> AttList;
	std::list<BattlePawn*> OtherAttList;
	void CallEraseAttList(const BattlePawn* taget);
	void CallEraseOtherList(const BattlePawn* taget);
	

public:
	BattlePawn();
	~BattlePawn();
};

