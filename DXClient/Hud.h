#pragma once
#include<ComScript.h>

class Player;
class Render2DSprite;
class Hud : public ComScript
{
private:
	SPTR<Player> m_Player;
	SPTR<Render2DSprite> m_HPBar;
	SPTR<Render2DSprite> m_MPBar;
	float CurHPFill;
	float afterHPFill;
	float subHPFill;
	float CurMPFill;
	float afterMPFill;
	float subMPFill;
public:
	bool Init() override;
	void Update() override;
	void LateUpdate() override;
	void DebugRender() override;
private:
	void HPUpdate();
	void MPUpdate();
public:
	void SetPlayer(SPTR<Actor> player);
public:
	Hud();
	~Hud();
};

