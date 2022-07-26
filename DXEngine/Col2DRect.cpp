#include "Col2DRect.h"
#include "DxDebug.h"

bool Col2DRect::ColCheck(ComCol * _OtherCol)
{
	switch (_OtherCol->GetColType())
	{
	case CT_NONE:
		break;
	case CT_2DPOINT:
		//GameMath::RectToPoint(this->Data, ((Col2DPoint*)_OtherCol)->Data);
		break;
	case CT_2DRECT:
		return GameMath::RectToRect(this->Data, ((Col2DRect*)_OtherCol)->Data);
		break;
	case CT_2DCIRCLE:
		//GameMath::RectToCircle(this->Data, ((Col2DCircle*)_OtherCol)->Data);
		break;
	case CT_2DPOLY:
		break;
	case CT_3DRAY:
		break;
	case CT_3DSPHERE:
		break;
	case CT_3DAABB:
		break;
	case CT_3DOBB:
		break;
	case CT_3DMESH:
		break;
	case CT_MAX:
		break;
	default:
		break;
	}
	return false;
}

void Col2DRect::DebugRender()
{
	DxDebug::DrawRect(GetWorldSubPosition(), GetLocalSubScale(), Color4f(0.2f, 0.8f, 0.2f), GetLocalSubRotate().z);
}

void Col2DRect::ColDataUpdate()
{
	Data.Position = GetWorld2DSubPosition();
	Data.Size = GetWorld2DSubScale();

	Data.Size.FABS();
}

Col2DRect::Col2DRect() : ComCol(CT_2DRECT)
{
}


Col2DRect::~Col2DRect()
{
}
