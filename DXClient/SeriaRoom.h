#pragma once
#include<Level.h>

class Fade;
class Player;
class Actor;
class MySoundPlayer;
class SeriaRoom : public Level::LevelScript
{
private:
	SPTR<Actor> m_Camera;
	SPTR<Actor> m_UICamera;
	SPTR<Actor> m_Player;
	SPTR<Player> m_ComPlayer;
	SPTR<Actor> m_Mouse;
	SPTR<Actor> m_Background;
	SPTR<Fade> m_Fade;
public:
	virtual bool Loading() override; // 씬이 로딩되지 않았을때 한번만 실행
	virtual void Start() override;
	virtual void Update() override;
	virtual void LateUpdate()override;
	virtual void End() override;
	virtual void DebugRender() override;

public:
	SeriaRoom();
	~SeriaRoom();
};

