#pragma once
#include<Level.h>

class MySoundPlayer;
class Render2DSprite;
class TilteLoading : public Level::LevelScript
{
private:
	SPTR<Actor> m_Camera;
	SPTR<Actor> m_Back;
	SPTR<Actor> loading;
	SPTR<Render2DSprite> rot;
	SPTR<MySoundPlayer> m_Sound;
	bool isLoading;
public:
	virtual bool Loading() override; // ���� �ε����� �ʾ����� �ѹ��� ����
	virtual void Start() override;
	virtual void Update() override;
	virtual void LateUpdate()override;
	virtual void End() override;
	virtual void DebugRender() override;
public:
	unsigned int DataLoad(void *);
public:
	TilteLoading();
	~TilteLoading();
};

