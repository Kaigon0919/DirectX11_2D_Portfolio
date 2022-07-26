#pragma once
#include <Component.h>
class ComCol;
class Fade;
class Player;
class Gate : public Component
{
public:
	enum GateType
	{
		GT_LEVELGATE,
		GT_POSGATE,
		GT_MAX
	};
private:
	std::wstring NextLevelName;
	Vector3f NextLevelPos;
	GateType type;
	bool m_bNext;
	SPTR<Fade> m_Fade;
	SPTR<Player> player;
public:
	bool Init();
	void Update() override;
	void LateUpdate() override;
	void DebugRender() override;
private:
	void ColEnter(ComCol* , ComCol* other);
	void ColStay(ComCol* , ComCol* other);
	void ColExit(ComCol* , ComCol* other);
public:
	void SetNextLevel(const std::wstring next);
	void SetNextPos(const Vector3f& Pos);
	void SetType(GateType _type);
	void SetSprite(const wchar_t * sprite);
	void SetFaid(SPTR<Fade> fade);
public:
	Gate();
	~Gate();
};

