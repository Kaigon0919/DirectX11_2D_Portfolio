#pragma once
#include<VectorData.h>

struct AniEventData
{
	unsigned int StartFrame;
	unsigned int EndFrame;
	Vector2f Position;
	Vector2f Scale;
};
struct SaveAniData
{
	wchar_t AniName[1024];
	unsigned int StartFrame;
	unsigned int EndFrame;
	float DefTime;
	bool isLoop;
};

struct GateData
{
	Vector2f Pos;
	Vector2f Scale;
	int Mode;
	wchar_t NextLevel[1024];
	Vector2f NextPos;
};

struct ObjectData
{
	Vector2f Pos;
	wchar_t SpriteName[1024];
};

struct MonData
{
	Vector2f Pos;
	int MonType;
};