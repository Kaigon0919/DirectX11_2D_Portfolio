#pragma once
#include"VectorData.h"

struct VertexData
{
public:
	VertexData() {}
	~VertexData() {}
public:
	Vector4f Position;
	Color4f Color;

	static unsigned int TypeSize()
	{
		return static_cast<unsigned int>(sizeof(VertexData));
	}
};

struct UVVertexData
{
public:
	UVVertexData() {}
	~UVVertexData() {}
public:
	Vector4f Position;
	Color4f Color;
	Vector2f TexUV;

	static unsigned int TypeSize()
	{
		return static_cast<unsigned int>(sizeof(UVVertexData));
	}
};

struct TexVertexData
{
public:
	TexVertexData() {}
	~TexVertexData() {}
public:
	Vector4f Position;
	Vector2f TexUV;

	static unsigned int TypeSize()
	{
		return static_cast<unsigned int>(sizeof(TexVertexData));
	}
};
struct IDX16
{
public:
	IDX16() : _1(), _2(), _3() {}
	IDX16(unsigned short __1, unsigned short __2, unsigned short __3 ) : _1(__1), _2(__2), _3(__3) {}
public:
	union 
	{
		struct
		{
			unsigned short _1, _2, _3;
		};
		unsigned short pWord[3];
	};
public:
	inline static unsigned int MemSize()
	{
		return static_cast<unsigned int>(sizeof(unsigned short));
	}
	unsigned short& operator[](const size_t idx)
	{
		if (idx >= (sizeof(pWord)/sizeof(unsigned short)))
		{
			return pWord[sizeof(pWord) - 1];
		}
		return pWord[idx];
	}
	const unsigned short& operator[](const size_t idx) const
	{
		if (idx >= (sizeof(pWord) / sizeof(unsigned short)))
		{
			return pWord[sizeof(pWord) - 1];
		}
		return pWord[idx];
	}
};

class IDX32
{
public:
	IDX32() : _1(), _2(), _3() {}
	IDX32(unsigned long __1, unsigned long __2, unsigned long __3) : _1(__1), _2(__2), _3(__3) {}
public:
	union
	{
		struct
		{
			unsigned long _1, _2, _3;
		};
		unsigned long pWord[3];
	};
public:
	static unsigned int MemSize()
	{
		return static_cast<unsigned int>(sizeof(unsigned long));
	}
	unsigned long& operator[](const size_t idx)
	{
		if (idx >= (sizeof(pWord) / sizeof(unsigned long)))
		{
			return pWord[sizeof(pWord) - 1];
		}
		return pWord[idx];
	}
	const unsigned long& operator[](const size_t idx) const
	{
		if (idx >= (sizeof(pWord) / sizeof(unsigned long)))
		{
			return pWord[sizeof(pWord) - 1];
		}
		return pWord[idx];
	}
};