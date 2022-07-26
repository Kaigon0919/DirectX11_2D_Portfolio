#include "LoadingDebugScript.h"

#include<DxDebug.h>


LoadingDebugScript::LoadingDebugScript()
{
}


LoadingDebugScript::~LoadingDebugScript()
{
}

bool LoadingDebugScript::Init()
{
	return true;
}

void LoadingDebugScript::Update()
{

}

void LoadingDebugScript::DebugRender()
{
	DxDebug::DrawRect(Vector3f(), Scale , Color4f());
}