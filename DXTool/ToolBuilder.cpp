#include "stdafx.h"
#include "ToolBuilder.h"
#include"ToolBuildScript.h"
#include<MiddleStart.h>
#include<Level.h>

bool ToolBuilder::Build()
{
	new int;

	SPTR<Level> Level = Level::CreateLevel<ToolBuildScript>(L"ToolLevel");

	return true;
}

ToolBuilder::ToolBuilder()
{
}


ToolBuilder::~ToolBuilder()
{
}
