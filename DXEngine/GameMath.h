#pragma once
#include"VectorData.h"

class GameMath
{
public:
	static bool RectToRect(const FRect& _Left, const FRect& _Right)
	{
		if (_Left.Left() > _Right.Right())
		{
			return false;
		}
		if (_Left.Right() < _Right.Left())
		{
			return false;
		}
		if (_Left.Top() < _Right.Bottom())
		{
			return false;
		}
		if (_Left.Bottom() > _Right.Top())
		{
			return false;
		}

		return true;
	}
	static bool RectToCircle(const FRect& _Left, const FRect& _Right)
	{
		FRect HR = _Left;
		FRect WR = _Left;

		HR.Size.y += _Right.Size.x;
		WR.Size.x += _Right.Size.x;

		if (RectToPoint(HR, _Right.Position) || RectToPoint(HR, _Right.Position))
		{
			return true;
		}

		if (CircleToPoint(_Right, _Left.LeftTop()) ||
			CircleToPoint(_Right, _Left.RightTop()) ||
			CircleToPoint(_Right, _Left.LeftBottom()) ||
			CircleToPoint(_Right, _Left.RightBottom()))
		{
			return true;
		}
		return false;
	}
	static bool RectToPoint(const FRect& _Left, const Vector2f& _Right)
	{
		if (_Left.Left() > _Right.x)
		{
			return false;
		}
		if (_Left.Right() < _Right.x)
		{
			return false;
		}
		if (_Left.Top() > _Right.y)
		{
			return false;
		}
		if (_Left.Bottom() < _Right.y)
		{
			return false;
		}
		return true;
	}
	static bool CircleToCircle(const FRect& _Left, const FRect& _Right)
	{
		float dis = (_Left.Position - _Right.Position).Length();

		if ( (_Left.Size.x/2.0f) + (_Right.Size.x/2.0f) > dis)
		{
			return true;
		}
		return false;
	}
	static bool CircleToPoint(const FRect& _Left, const Vector2f& _Right)
	{
		float dis = (_Left.Position - _Right).Length();

		if ((_Left.Size.x / 2.0f) > dis)
		{
			return true;
		}
		return false;
	}
	static bool PointToPoint(const Vector2f& _Left, const Vector2f& _Right) {
		return _Left == _Right;
	}
public:
	GameMath();
	~GameMath();
};

