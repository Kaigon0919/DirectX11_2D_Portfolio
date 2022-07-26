#include "VectorData.h"


Vector3f Vector3f::Zero = Vector3f(0.0f, 0.0f, 0.0f);
Vector3f Vector3f::One = Vector3f(1.0f,1.0f,1.0f);
Vector3f Vector3f::Right = Vector3f(1.0f, 0.0f, 0.0f);
Vector3f Vector3f::Up = Vector3f(0.0f, 1.0f, 0.0f);
Vector3f::operator Vector3i() const
{
	return Vector3i(static_cast<int>(x), static_cast<int>(y), static_cast<int>(z));
}

Vector3f::operator Vector4f() const
{
	return Vector4f(x, y, z, 1);
}

Vector3i::operator Vector3f() const
{
	return Vector3f(static_cast<float>(x), static_cast<float>(y), static_cast<float>(z));
}

Vector4f::operator Vector3f() const
{
	return Vector3f(x, y, z);
}
Vector2i::operator Vector2f() const
{
	return Vector2f(static_cast<float>(x), static_cast<float>(y));
}

Vector2i::operator Vector3f() const
{
	return Vector3f(static_cast<float>(x), static_cast<float>(y), 0.0f);
}

Vector2f::operator Vector2i() const
{
	return Vector2i((int)x, (int)y);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
// Matrix4x4
///////////////////////////////////////////////////////////////////////////////////////////////////////
