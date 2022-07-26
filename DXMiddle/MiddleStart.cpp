#include "MiddleStart.h"

#include <InputManager.h>
#include<PathManager.h>
#include<ResMgr.h>
#include<Tex.h>
#include<GameSprite.h>
#include<MySound.h>
void MiddleStart::Init()
{
	PathManager::RootToCreatePath(L"Tex");
	PathManager::RootToCreatePath(L"Sound");
	PathManager::RootToCreatePath(L"Data");
	PathManager::PlusCreatePath(L"Data",L"MapData",L"MapData");
	PathManager::PlusCreatePath(L"Data", L"AniData", L"AniData");
	PathManager::PlusCreatePath(L"Data", L"SubTransData", L"SubTransData");
	PathManager::PlusCreatePath(L"Data", L"MonsterBat", L"MonsterBat");

	// Move.
	InputManager::CreateKey(L"LEFT", VK_LEFT);
	InputManager::CreateKey(L"RIGHT", VK_RIGHT);
	InputManager::CreateKey(L"UP", VK_UP);
	InputManager::CreateKey(L"DOWN", VK_DOWN);

	// Base.
	InputManager::CreateKey(L"Z", L'Z');
	InputManager::CreateKey(L"X", L'X');
	InputManager::CreateKey(L"C", L'C');
	// Qick Slot.
	InputManager::CreateKey(L"A", L'A');
	InputManager::CreateKey(L"S", L'S');
	InputManager::CreateKey(L"D", L'D');
	InputManager::CreateKey(L"F", L'F');
	InputManager::CreateKey(L"G", L'G');
	InputManager::CreateKey(L"H", L'H');

	InputManager::CreateKey(L"Q", L'Q');
	InputManager::CreateKey(L"W", L'W');
	InputManager::CreateKey(L"E", L'E');
	InputManager::CreateKey(L"R", L'R');
	InputManager::CreateKey(L"T", L'T');
	InputManager::CreateKey(L"Y", L'Y');

	InputManager::CreateKey(L"1", L'1');
	InputManager::CreateKey(L"2", L'2');
	InputManager::CreateKey(L"3", L'3');
	InputManager::CreateKey(L"4", L'4');
	InputManager::CreateKey(L"5", L'5');
	InputManager::CreateKey(L"6", L'6');
	// Mouse.
	InputManager::CreateKey(L"LButton", VK_LBUTTON);
	InputManager::CreateKey(L"RButton", VK_RBUTTON);

}

MiddleStart::MiddleStart()
{
}


MiddleStart::~MiddleStart()
{
}
