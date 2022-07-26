#pragma once
#include"DXFont.h"

class DxDebug
{
public:
	static void DrawStr(const wchar_t* str, float size, Vector2i pos, Color4f color, FW1_TEXT_FLAG flag = FW1_TOP);
	static void DrawRect(Vector3f _Pos, const Vector3f& _Scale, const Color4f& _Color, const float _Angle = 0.0f);
public:
	DxDebug();
	~DxDebug();
};

