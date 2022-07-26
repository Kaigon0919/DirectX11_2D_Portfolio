#pragma once
#include<Level.h>
class ToolBuildScript : public Level::LevelScript
{
public:
	virtual bool Loading() override;
	virtual void LateUpdate() override;

	virtual void DebugRender() override;
public:
	ToolBuildScript();
	~ToolBuildScript();
};

