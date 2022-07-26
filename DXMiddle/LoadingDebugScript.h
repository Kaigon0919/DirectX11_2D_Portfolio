#pragma once
#include <ComScript.h>
#include <Render2DSprite.h>
#include <Com2DFrameAni.h>

class LoadingDebugScript : public ComScript
{
private:
	int* LoadingCount;
	int MaxCount;
	Vector3f Scale;

public:
	void SetLoadingCount(int* _LoadingCount, int _MaxCount)
	{
		LoadingCount = _LoadingCount;
		MaxCount = _MaxCount;
	}

public:
	bool Init() override;
	void Update() override;
	void DebugRender() override;

public:
	LoadingDebugScript();
	~LoadingDebugScript();
};


