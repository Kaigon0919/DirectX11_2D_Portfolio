#include "FirstCore.h"
#include"SeriaRoom.h"
#include"Village.h"
#include"TilteLoading.h"
#include"Stage1.h"
#include"Stage2.h"
#include"StageBoss.h"
#include<MiddleStart.h>
FirstCore::FirstCore()
{

}


FirstCore::~FirstCore()
{

}

bool FirstCore::Build()
{
	//_CrtSetBreakAlloc(297);
	MiddleStart::Init();

	Level::CreateLevel<TilteLoading>(L"Tiltle");
	Level::CreateLevel<SeriaRoom>(L"SeriaRoom");
	Level::CreateLevel<Village>(L"Village");
	Level::CreateLevel<Stage1>(L"Stage1");
	Level::CreateLevel<Stage2>(L"Stage2");
	Level::CreateLevel<StageBoss>(L"StageBoss");
	Level::ChangeLevel(L"Tiltle");

	return true;
}
