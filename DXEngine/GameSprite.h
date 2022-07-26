#pragma once
#include"Resource.h"
#include"VectorData.h"

class Tex;
class DxSampler;
class GameSprite : public Resource
{
private:
	SPTR<Tex> TEX;
	SPTR<DxSampler> SMP;
	std::vector<FRect> m_UVMap;
	
public:
	const Vector4f& IndexToUV(const int _index)
	{
		return m_UVMap[_index];
	}
public:
	size_t CutSize() const
	{
		return m_UVMap.size();
	}
public:
	DEFCREATOR(GameSprite,std::wstring)
		DEFCREATORFUNC(const wchar_t* _TexName, unsigned int _CountX = 1, unsigned int _CountY = 1, const wchar_t* _SmpName = L"DEFSMP")
		DEFCREATORFUNCPARA(_TexName, _CountX ,_CountY , _SmpName)
		DEFCREATOREND

public:
	void Update();

public:
	bool Create(const wchar_t* _TexName, unsigned int _CountX = 1, unsigned int _CountY = 1, const wchar_t* _SmpName = L"DEFSMP");
	size_t PushUV(Vector4f _uv);
	FRect CalUV(size_t _index);
	Vector2i GetImageSize()const;
	Vector2i GetSpriteImageSize(size_t index = 0)const;
public:
	GameSprite();
	~GameSprite();
};

