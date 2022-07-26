#include "stdafx.h"
#include "SpriteScript.h"
#include<Camera.h>

bool SpriteScript::Init()
{
	cCam = AddComponent<Camera>();
	cCam->GetTransform()->SetLocalPosition(0.0f, 0.0f, -10.0f);
	cCam->OnViewGroup(0);
	return true;
}

void SpriteScript::Update()
{
	float heel = InputManager::GetMouseWHeel() / 120.0f * 0.01f;
	if (heel != 0)
	{
		cCam->AddZoom(heel);
	}
}

SpriteScript::SpriteScript()
{
}


SpriteScript::~SpriteScript()
{
}
