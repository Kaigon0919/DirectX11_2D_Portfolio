#pragma once
#include<Level.h>

class MySoundPlayer;
class Fade;
class Player;
class Village : public Level::LevelScript
{
private:
	SPTR<Actor> m_Camera;
	SPTR<Actor> m_UICamera;
	SPTR<Actor> m_Player;
	SPTR<Actor> m_Mouse;
	SPTR<Fade> m_Fade;
	SPTR<Player> m_ComPlayer;
	SPTR<Actor> m_Background;
public:
	virtual bool Loading() override; // ���� �ε����� �ʾ����� �ѹ��� ����
	virtual void Start() override;
	virtual void Update() override;
	virtual void LateUpdate()override;
	virtual void End() override;
	virtual void DebugRender() override;

public:
	Village();
	~Village();
};

