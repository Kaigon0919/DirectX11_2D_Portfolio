#pragma once
#include "ComCol.h"

class Col2DRect : public ComCol
{
private:
	FRect Data;

public:
	bool ColCheck(ComCol* _OtherCol)override;
	void DebugRender() override;

	void ColDataUpdate()override;

public:
	Col2DRect();
	~Col2DRect();
};

