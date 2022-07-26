#pragma once
#include<memory>

// XMVECTOR등이 있는 헤더.
#include <DirectXPackedVector.h> 


struct Vector2i;
struct Vector2f;
struct Vector3i;
struct Vector3f;
struct Vector4f;

typedef Vector4f Color4f;



struct Vector4f
{
public:
	Vector4f() : x(), y(), z(), w(1.0f) {}
	Vector4f(float x, float y, float z) : x(x), y(y), z(z), w(1.0f) {}
	Vector4f(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}
	Vector4f(const Vector4f& ref) : x(ref.x), y(ref.y), z(ref.z), w(ref.w) {}
	Vector4f(const DirectX::XMFLOAT4& ref) : m_XMVector4(ref) {  }
	Vector4f(const DirectX::XMVECTOR& ref) { DirectX::XMStoreFloat4(&m_XMVector4, ref); }
public:
	union
	{
		DirectX::XMFLOAT4 m_XMVector4;
		struct
		{
			float x;
			float y;
			float z;
			float w;
		};
		float pf[4];
	};
public:
	Vector4f& operator=(const Vector4f& ref)
	{
		x = ref.x;
		y = ref.y;
		z = ref.z;
		w = ref.w;
		return *this;
	}
	Vector4f operator*(const Vector4f& ref)
	{
		Vector4f Temp;
		Temp.x = x * ref.x;
		Temp.y = y * ref.y;
		Temp.z = z * ref.z;
		Temp.w = w * ref.w;
		return Temp;
	}
	//Vector4f& operator=(const DirectX::XMVECTOR& ref)
	//{
	//	DirectX::XMStoreFloat4(&m_XMVector4, ref);
	//	return *this;
	//}
	float Dot(const Vector4f& ref) const
	{
		Vector4f temp;
		DirectX::XMVECTOR vec1 = DirectX::XMLoadFloat4(&m_XMVector4);
		DirectX::XMVECTOR vec2 = DirectX::XMLoadFloat4(&ref.m_XMVector4);
		DirectX::XMStoreFloat4(&temp.m_XMVector4, DirectX::XMVector4Dot(vec1, vec2));
		return temp.w;
	}
	Vector4f Cross(const Vector4f& ref)const
	{
		Vector4f temp;
		DirectX::XMVECTOR vec1 = DirectX::XMLoadFloat4(&m_XMVector4);
		DirectX::XMVECTOR vec2 = DirectX::XMLoadFloat4(&ref.m_XMVector4);
		DirectX::XMStoreFloat4(&temp.m_XMVector4, DirectX::XMVector3Cross(vec1, vec2));
		return temp;
	}

	float& operator[](const size_t index)
	{
		if (index >= (sizeof(pf) / sizeof(float)))
		{
			return pf[3];
		}
		return pf[index];
	}
	const float& operator[](const size_t index) const
	{
		if (index >= (sizeof(pf) / sizeof(float)))
		{
			return pf[3];
		}
		return pf[index];
	}
	operator Vector3f()const;
	operator DirectX::XMFLOAT4()const
	{
		return m_XMVector4;
	}

	operator DirectX::XMVECTOR()const
	{
		return DirectX::XMLoadFloat4(&m_XMVector4);
	}
};
struct Vector3f
{
public:
	Vector3f() : x(), y(), z() {}
	Vector3f(float x, float y, float z) : x(x), y(y), z(z) {}
	Vector3f(const Vector3f& ref) : x(ref.x), y(ref.y), z(ref.z) {}
	Vector3f(const DirectX::XMFLOAT3& ref) : m_XMVector3(ref) {  }
	Vector3f(const DirectX::XMVECTOR& ref) { DirectX::XMStoreFloat3(&m_XMVector3, ref); }

public:
	static Vector3f One;
	static Vector3f Zero;
	static Vector3f Right;
	static Vector3f Up;
public:
	union
	{
		DirectX::XMFLOAT3 m_XMVector3;
		struct
		{
			float x;
			float y;
			float z;
		};
		float pf[3];
	};
public:
	Vector3f operator-()const
	{
		return (*this)*-1.0f;
	}
	Vector3f& operator=(const Vector3f& ref)
	{
		x = ref.x;
		y = ref.y;
		z = ref.z;
		return *this;
	}
	Vector3f& operator=(const DirectX::XMFLOAT3& ref)
	{
		m_XMVector3 = ref;
		return *this;
	}
	Vector3f& operator=(const DirectX::XMVECTOR& ref)
	{
		DirectX::XMStoreFloat3(&m_XMVector3, ref);
		return *this;
	}
	Vector3f& operator+=(const Vector3f& ref)
	{
		x += ref.x;
		y += ref.y;
		z += ref.z;
		return *this;
	}
	Vector3f& operator-=(const Vector3f& ref)
	{
		x -= ref.x;
		y -= ref.y;
		z -= ref.z;
		return *this;
	}
	Vector3f& operator*=(const Vector3f& ref)
	{
		x *= ref.x;
		y *= ref.y;
		z *= ref.z;
		return *this;
	}
	Vector3f& operator*=(const float& ref)
	{
		x *= ref;
		y *= ref;
		z *= ref;
		return *this;
	}
	Vector3f& operator/=(const Vector3f& ref)
	{
		x /= ref.x;
		y /= ref.y;
		z /= ref.z;
		return *this;
	}
	Vector3f& operator/=(const float ref)
	{
		x /= ref;
		y /= ref;
		z /= ref;
		return *this;
	}
	Vector3f operator+(const Vector3f& ref) const
	{
		return Vector3f(x + ref.x, y + ref.y, z + ref.z);
	}
	Vector3f operator-(const Vector3f& ref) const
	{
		return Vector3f(x - ref.x, y - ref.y, z - ref.z);
	}
	Vector3f operator*(const float scala) const
	{
		return Vector3f(x * scala, y * scala, z * scala);
	}
	Vector3f operator*(const Vector3f& other) const
	{
		return Vector3f(x * other.x, y * other.y, z * other.z);
	}
	Vector3f operator/(const float scala) const
	{
		return Vector3f(x / scala, y / scala, z / scala);
	}
	Vector3f operator/(const Vector3f& other) const
	{
		return Vector3f(x / other.x, y / other.y, z / other.z);
	}
	float Dot(const Vector3f& ref) const
	{
		// 고민하다. 그냥 내가 직접 계산할지, XMVECTOR 연산을 할지.
		Vector3f temp;
		DirectX::XMVECTOR vec1 = XMLoadFloat3(&m_XMVector3);
		DirectX::XMVECTOR vec2 = XMLoadFloat3(&ref.m_XMVector3);
		DirectX::XMStoreFloat3(&temp.m_XMVector3, DirectX::XMVector3Dot(vec1, vec2));
		return temp.x;
		//return (x * ref.x + y * ref.y + z * ref.z);
	}
	Vector3f Cross(const Vector3f& ref) const
	{
		Vector3f temp;
		DirectX::XMVECTOR vec1 = XMLoadFloat3(&m_XMVector3);
		DirectX::XMVECTOR vec2 = XMLoadFloat3(&ref.m_XMVector3);
		DirectX::XMStoreFloat3(&temp.m_XMVector3, DirectX::XMVector3Cross(vec1, vec2));
		return temp;
		//return Vector3f(y * ref.z - z * ref.y, z * ref.x - x * ref.z, x * ref.y - y * ref.x);
	}
	float Length()const
	{
		return sqrtf(x*x + y*y + z*z);
	}
	void Normalize()
	{
		float len =  Length();
		if (len == 0)
		{
			return;
		}
		*this /= Length();
	}
	Vector3f GetNormalize() const
	{
		Vector3f returnValue = *this;
		returnValue.Normalize();
		return returnValue;
	}

	float& operator[](const size_t index)
	{
		if (index >= (sizeof(pf) / sizeof(float)))
		{
			return pf[2];
		}
		return pf[index];
	}
	const float& operator[](const size_t index) const
	{
		if (index >= (sizeof(pf) / sizeof(float)))
		{
			return pf[2];
		}
		return pf[index];
	}
	operator Vector3i()const;
	operator Vector4f()const;
	operator DirectX::XMFLOAT3()const
	{
		return m_XMVector3;
	}
	operator DirectX::XMVECTOR()const
	{
		return DirectX::XMLoadFloat3(&m_XMVector3);
	}
};


struct Vector3i
{
public:
	Vector3i() : x(), y(), z() {}
	Vector3i(int x, int y, int z) : x(x), y(y), z(z) {}
	Vector3i(const Vector3i& ref) : x(ref.x), y(ref.y), z(ref.z) {}

public:
	int x;
	int y;
	int z;
public:
	Vector3i& operator=(const Vector3i& ref)
	{
		x = ref.x;
		y = ref.y;
		z = ref.z;
		return *this;
	}

	Vector3i& operator+=(const Vector3i& ref)
	{
		x += ref.x;
		y += ref.y;
		z += ref.z;
		return *this;
	}
	Vector3i& operator-=(const Vector3i& ref)
	{
		x -= ref.x;
		y -= ref.y;
		z -= ref.z;
		return *this;
	}
	Vector3i& operator*=(const Vector3i& ref)
	{
		x *= ref.x;
		y *= ref.y;
		z *= ref.z;
		return *this;
	}
	Vector3i& operator/=(const Vector3i& ref)
	{
		x /= ref.x;
		y /= ref.y;
		z /= ref.z;
		return *this;
	}
	Vector3i operator+(const Vector3i& ref) const
	{
		return Vector3i(x + ref.x, y + ref.y, z + ref.z);
	}
	Vector3i operator-(const Vector3i& ref) const
	{
		return Vector3i(x - ref.x, y - ref.y, z - ref.z);
	}
	Vector3i operator*(const float scala) const
	{
		return Vector3i(static_cast<int>(x * scala), static_cast<int>(y * scala), static_cast<int>(z * scala));
	}
	Vector3i operator/(const float scala) const
	{
		return Vector3i(static_cast<int>(x / scala), static_cast<int>(y / scala), static_cast<int>(z / scala));
	}
	operator Vector3f()const;
};

struct Vector2i
{
public:
	Vector2i() : x(), y() {}
	Vector2i(int x, int y) : x(x), y(y) {}

public:
	union 
	{
		struct 
		{
			int x;
			int y;
		};
		__int64 i64;
	};
public:
	Vector2i& operator=(const Vector2i& ref)
	{
		x = ref.x;
		y = ref.y;
		return *this;
	}

	Vector2i& operator+=(const Vector2i& ref)
	{
		x += ref.x;
		y += ref.y;
		return *this;
	}
	Vector2i& operator-=(const Vector2i& ref)
	{
		x -= ref.x;
		y -= ref.y;
		return *this;
	}
	Vector2i& operator*=(const Vector2i& ref)
	{
		x *= ref.x;
		y *= ref.y;
		return *this;
	}
	Vector2i& operator/=(const Vector2i& ref)
	{
		x /= ref.x;
		y /= ref.y;
		return *this;
	}
	Vector2i& operator/=(const int ref)
	{
		x /= ref;
		y /= ref;
		return *this;
	}
	Vector2i operator+(const Vector2i& ref) const
	{
		return Vector2i(x + ref.x, y + ref.y);
	}
	Vector2i operator-(const Vector2i& ref) const
	{
		return Vector2i(x - ref.x, y - ref.y);
	}
	Vector2i operator*(const Vector2i& ref) const
	{
		return Vector2i(x * ref.x, y * ref.y);
	}
	Vector2i operator*(const int scala) const
	{
		return Vector2i(x * scala, y * scala);
	}
	Vector2i operator*(const float scala) const
	{
		return Vector2i((int)(x * scala), (int)(y * scala));
	}
	Vector2i operator/(const int scala) const
	{
		return Vector2i(x / scala, y / scala);
	}
	Vector2i operator/(const float scala) const
	{
		return Vector2i((int)(x / scala), (int)(y / scala));
	}
	operator Vector2f()const;
	operator Vector3f()const;
};

struct Vector2f
{
public:
	Vector2f() : x(), y() {}
	Vector2f(float x, float y) : x(x), y(y) {}

public:
	float x;
	float y;
public:
	bool operator==(const Vector2f& ref) const
	{
		return (x == ref.x) && (y == ref.y);
	}
	Vector2f& operator=(const Vector2f& ref)
	{
		x = ref.x;
		y = ref.y;
		return *this;
	}

	Vector2f& operator+=(const Vector2f& ref)
	{
		x += ref.x;
		y += ref.y;
		return *this;
	}
	Vector2f& operator-=(const Vector2f& ref)
	{
		x -= ref.x;
		y -= ref.y;
		return *this;
	}
	Vector2f& operator*=(const Vector2f& ref)
	{
		x *= ref.x;
		y *= ref.y;
		return *this;
	}
	Vector2f& operator/=(const Vector2f& ref)
	{
		x /= ref.x;
		y /= ref.y;
		return *this;
	}
	Vector2f operator+(const Vector2f& ref) const
	{
		return Vector2f(x + ref.x, y + ref.y);
	}
	Vector2f operator-(const Vector2f& ref) const
	{
		return Vector2f(x - ref.x, y - ref.y);
	}
	Vector2f operator*(const float scala) const
	{
		return Vector2f(x * scala, y * scala);
	}
	Vector2f operator/(const float scala) const
	{
		return Vector2f(x / scala, y / scala);
	}
	Vector2f& operator/=(const float scala)
	{
		x /= scala;
		y /= scala;
		return *this;
	}
	float Length()const
	{
		return sqrtf(x*x + y*y );
	}
	void Normalize()
	{
		*this /= Length();
	}
	Vector2f GetNormalize() const
	{
		Vector2f returnValue = *this;
		returnValue.Normalize();
		return returnValue;
	}
	void FABS()
	{
		x = fabsf(x);
		y = fabsf(y);
	}

	operator Vector2i()const;
};

struct Matrix4x4
{
public:
	Matrix4x4() :m_Matirx{ 0 } { Identity(); }
	Matrix4x4(const Matrix4x4 & ref) {memcpy_s(m_Matirx, sizeof(m_Matirx), ref.m_Matirx, sizeof(ref.m_Matirx));}
	Matrix4x4(const DirectX::XMFLOAT4X4 & ref) : m_XMf4x4(ref) {}
	Matrix4x4(const DirectX::XMMATRIX & ref) {	DirectX::XMStoreFloat4x4(&m_XMf4x4, ref);	}
	~Matrix4x4() {}
public:
	union
	{
		DirectX::XMFLOAT4X4 m_XMf4x4;
		float m_Matirx[4][4];
		struct
		{
			Vector4f vec0;
			Vector4f vec1;
			Vector4f vec2;
			Vector4f vec3;
		};
	};
public:
	enum AXIS
	{
		AXIS_X,
		AXIS_Y,
		AXIS_Z,
	};
public:
	void Zero()
	{
		memset(m_Matirx, 0, sizeof(m_Matirx));
	}
	void Identity()
	{
		DirectX::XMStoreFloat4x4(&m_XMf4x4, DirectX::XMMatrixIdentity());
	}

	Matrix4x4 operator*(const Matrix4x4& ref) const
	{
		return Mul(ref);
	}
	Vector4f operator*(const Vector4f& ref)
	{
		return Mul(ref);
	}
	Matrix4x4& operator=(const Matrix4x4& ref)
	{
		memcpy_s(m_Matirx, sizeof(m_Matirx), ref.m_Matirx, sizeof(ref.m_Matirx));
		return *this;
	}
	Matrix4x4& operator=(const  DirectX::XMMATRIX& ref)
	{
		DirectX::XMStoreFloat4x4(&m_XMf4x4, ref);
		return *this;
	}
	operator DirectX::XMMATRIX()const
	{
		return DirectX::XMLoadFloat4x4(&m_XMf4x4);
	}
	Matrix4x4 Mul(const Matrix4x4& ref) const
	{
		Matrix4x4 temp;
		DirectX::XMStoreFloat4x4(&temp.m_XMf4x4, DirectX::XMMatrixMultiply(*this, ref));
		return temp;
	}
	Vector4f Mul(const Vector4f& ref)
	{
		Vector4f temp;
		DirectX::XMStoreFloat4(&temp.m_XMVector4, DirectX::XMVector4Transform(ref, *this));
		return temp;
	}
	void SetScale(const Vector3f& ref)
	{
		Identity();
		DirectX::XMStoreFloat4x4( &m_XMf4x4 ,DirectX::XMMatrixScaling(ref.x, ref.y, ref.z));
	}
	void SetRotationDegree(const Vector3f& ref)
	{
		Vector3f radianVec = ref;
		radianVec *= (DirectX::XM_PI / 180.0f);
		SetRotation(radianVec);
	}
	void SetRotation(const Vector3f& ref)
	{
		Identity();
		DirectX::XMStoreFloat4x4(&m_XMf4x4, (DirectX::XMMatrixRotationX(ref.x) * DirectX::XMMatrixRotationY(ref.y) * DirectX::XMMatrixRotationZ(ref.z) ) );
	}
	void SetPosition(const Vector3f& ref)
	{
		Identity();
		DirectX::XMStoreFloat4x4(&m_XMf4x4, DirectX::XMMatrixTranslation(ref.x, ref.y, ref.z));
	}

	void ViewAtLH(const Vector4f& eye, const Vector4f& focus, const Vector4f& up)
	{
		Identity();
		DirectX::XMStoreFloat4x4(&m_XMf4x4, DirectX::XMMatrixLookAtLH(eye, focus, up));
	}
	void ViewToLH(const Vector4f& eye,	const Vector4f& eyeDir,	const Vector4f& up)
	{
		Identity();
		DirectX::XMStoreFloat4x4(&m_XMf4x4, DirectX::XMMatrixLookToLH(eye, eyeDir, up));
	}
	void PersFov(float _fov, float _width, float _height, float _near, float _far)
	{
		Identity();
		DirectX::XMStoreFloat4x4(&m_XMf4x4, DirectX::XMMatrixPerspectiveFovLH(_fov, _width / _height, _near, _far));
	}

	void PersFovDegree(float _fov, float _width, float _height, float _near, float _far)
	{
		Identity();
		DirectX::XMStoreFloat4x4(&m_XMf4x4, DirectX::XMMatrixPerspectiveFovLH(_fov * DirectX::XM_PI /180.0f, _width / _height, _near, _far));
	}

	void Pers(float _width, float _height, float _near, float _far)
	{
		Identity();
		DirectX::XMStoreFloat4x4(&m_XMf4x4, DirectX::XMMatrixPerspectiveLH(_width, _height, _near, _far));
	}

	void Orth(float _Width, float _Height, float _Near, float _Far)
	{
		Identity();
		DirectX::XMStoreFloat4x4(&m_XMf4x4, DirectX::XMMatrixOrthographicLH(_Width, _Height, _Near, _Far));
	}

	void TransPose()
	{
		DirectX::XMStoreFloat4x4(&m_XMf4x4, DirectX::XMMatrixTranspose(*this));
	}
	Matrix4x4 ReturnTransPose()const
	{
		Matrix4x4 returnMat = *this;
		returnMat.TransPose();
		return returnMat;
	}
	Vector3f ColumnVector3f(unsigned int columnIndex) const
	{
		Vector3f returnVector = Vector3f();
		for (unsigned int i = 0; i < 3; ++i)
		{
			returnVector[i] = m_Matirx[i][columnIndex];
		}
		return returnVector;
	}

	Vector3f GetScale()const
	{
		return Vector3f(m_Matirx[0][0], m_Matirx[1][1], m_Matirx[2][2]);
	}
	Vector3f GetPosition()const
	{
		return Vector3f(vec3);
	}
	static Matrix4x4 CreateTransPose(const Matrix4x4& refMat)
	{
		Matrix4x4 returnMatrix;
		DirectX::XMStoreFloat4x4(&returnMatrix.m_XMf4x4, DirectX::XMMatrixTranspose(refMat));
		return returnMatrix;
	}

	static Matrix4x4 RotateX(float radian)
	{
		Matrix4x4 temp;
		DirectX::XMStoreFloat4x4(&temp.m_XMf4x4, DirectX::XMMatrixRotationX(radian));
		return temp;
	}
	static 	Matrix4x4 RotateY(float radian)
	{
		Matrix4x4 temp;
		DirectX::XMStoreFloat4x4(&temp.m_XMf4x4, DirectX::XMMatrixRotationY(radian));
		return temp;
	}
	static Matrix4x4 RotateZ(float radian)
	{
		Matrix4x4 temp;
		DirectX::XMStoreFloat4x4(&temp.m_XMf4x4, DirectX::XMMatrixRotationZ(radian));
		return temp;
	}
	static Matrix4x4 RotateXDegree(float degree)
	{
		return RotateX(degree * 3.1415f / 180.0f);
	}
	static Matrix4x4 RotateYDegree(float degree)
	{
		return RotateY(degree * 3.1415f / 180.0f);
	}
	static Matrix4x4 RotateZDegree(float degree)
	{
		return RotateZ(degree * 3.1415f / 180.0f);
	}
	static Matrix4x4 CreateScale(const Vector3f& ref)
	{
		Matrix4x4 temp;
		temp.SetScale(ref);
		return temp;
	}
	static Matrix4x4 CreateRotate(const Vector3f& ref)
	{
		Matrix4x4 temp;
		temp.SetRotationDegree(ref);
		return temp;
	}
	static Matrix4x4 CreateTranslation(const Vector3f& ref)
	{
		Matrix4x4 temp;
		temp.SetPosition(ref);
		return temp;
	}
};


struct FRect
{
public:
	Vector2f Position;
	Vector2f Size;
public:
	FRect() : Position(), Size() {}
	FRect(const Vector2f& _pos, const Vector2f& _size) : Position(_pos), Size(_size) {}
	FRect(const float _posX,const float _posY, const float _sizeX, const float _sizeY) : Position(_posX,_posY), Size(_sizeX,_sizeY) {}
	FRect(const FRect& ref) : Position(ref.Position), Size(ref.Size) {}
	FRect(const Vector4f& ref) : Position(ref.x,ref.y), Size(ref.z,ref.w) {}

public:
	FRect operator+(const FRect& ref)const
	{
		FRect temp;
		temp.Position = Position + ref.Position;
		temp.Size = Size + ref.Size;
		return temp;
	}
	FRect operator-(const FRect& ref)const
	{
		FRect temp;
		temp.Position = Position - ref.Position;
		temp.Size = Size - ref.Size;
		return temp;
	}
	FRect& operator+=(const FRect& ref)
	{
		Position += ref.Position;
		Size += ref.Size;
	}
	FRect& operator-=(const FRect& ref)
	{
		Position -= ref.Position;
		Size -= ref.Size;
	}
	operator Vector4f() const
	{
		return Vector4f(Position.x, Position.y, Size.x, Size.y);
	}
	float Left()const				{	return Position.x - Size.x/2.0f;								}
	float Right()const				{	return Position.x + Size.x/2.0f;								}
	float Top()const				{	return Position.y + Size.y/2.0f;								}
	float Bottom()const				{	return Position.y - Size.y/2.0f;								}
	
	Vector2f LeftTop()const			{	return Vector2f(Left()	, Top()		);							}
	Vector2f RightTop()const		{	return Vector2f(Right()	, Top()		);							}
	Vector2f LeftBottom()const		{	return Vector2f(Left()	, Bottom()	);							}
	Vector2f RightBottom()const		{	return Vector2f(Right()	, Bottom()	);							}
	
	Vector2f LeftCenter()const		{	return Vector2f(Left()		, Position.y	);					}
	Vector2f RightCenter()const		{	return Vector2f(Right()		, Position.y	);					}
	Vector2f TopCenter()const		{	return Vector2f(Position.x	, Top()			);					}
	Vector2f BottomCenter()const	{	return Vector2f(Position.x	, Bottom()		);					}
	
	
	int IntLeft()const				{	return (int)Left();												}
	int IntRight()const				{	return (int)Right();											}
	int IntTop()const				{	return (int)Top();												}
	int IntBottom()const			{	return (int)Bottom();											}
	
	Vector2i IntLeftTop()const		{	return LeftTop();												}
	Vector2i IntRightTop()const		{	return RightTop();												}
	Vector2i IntLeftBottom()const	{	return LeftBottom();											}
	Vector2i IntRightBottom()const	{	return RightBottom();											}
	
	Vector2i IntLeftCenter()const	{	return LeftCenter();											}
	Vector2i IntRightCenter()const	{	return RightCenter();											}
	Vector2i IntTopCenter()const	{	return TopCenter();												}
	Vector2i IntBottomCenter()const {	return BottomCenter();											}
};