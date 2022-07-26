#include "stdafx.h"
#include "ToolBuildScript.h"
#include<Camera.h>
#include<DXFont.h>

bool ToolBuildScript::Loading()
{
	SPTR<Actor> NewActor = GetLevel()->CreateActor();

	SPTR<Camera> Ptr = NewActor->AddComponent<Camera>(0);
	Ptr->OnViewGroup(0, 1, 2, 3, 4, 5);
	Ptr->GetTransform()->SetLocalPosition(Vector3f(0.0f, 0.0f, -100.0f));

	return false;
}
void ToolBuildScript::LateUpdate()
{

	
}
void ToolBuildScript::DebugRender()
{

}

ToolBuildScript::ToolBuildScript()
{
}


ToolBuildScript::~ToolBuildScript()
{
}
