#pragma once
#include <ComScript.h>
#include<Camera.h>
class SpriteScript : public ComScript
{
private:
	SPTR<Camera> cCam;

public:
	bool Init() override;
	void Update() override;
public:
	SpriteScript();
	~SpriteScript();
};

