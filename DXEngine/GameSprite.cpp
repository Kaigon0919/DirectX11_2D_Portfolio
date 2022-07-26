#include "GameSprite.h"
#include"Tex.h"
#include"DxSampler.h"


void GameSprite::Update()
{
	if (nullptr == TEX)
	{
		assert(false && L"GameSprite, Tex is nullptr");
		return;
	}

	if (nullptr == SMP)
	{
		assert(false && L"GameSprite, Sampler is nullptr");
		return;
	}

	TEX->Update();
	SMP->Update();
}

bool GameSprite::Create(const wchar_t * _TexName, unsigned int _CountX, unsigned int _CountY, const wchar_t * _SmpName)
{
	if (_CountX == 0)
	{
		return false;
	}

	if (_CountY == 0)
	{
		return false;
	}

	if (nullptr == (TEX = ResMgr<Tex>::Find(_TexName)))
	{
		assert(false && L"GameSprite not find Tex");
		return false;
	}

	if (nullptr == (SMP = ResMgr<DxSampler>::Find(_SmpName)))
	{
		assert(false && L"GameSprite not find Sampler");
		return false;
	}

	Vector2f size;
	size.x = 1.0f / (float)_CountX;
	size.y = 1.0f / (float)_CountY;

	for (size_t y = 0; y < _CountY; ++y)
	{
		for (size_t x = 0; x < _CountX; ++x)
		{
			FRect UV;
			UV.Position.x = size.x * (float)x;
			UV.Position.y = size.y * (float)y;
			UV.Size = size;
			m_UVMap.push_back(UV);
		}
	}
	return true;
}

size_t GameSprite::PushUV(Vector4f _uv)
{
	m_UVMap.push_back(_uv);

	return m_UVMap.size() - 1;
}

FRect GameSprite::CalUV(size_t _index)
{
	return m_UVMap[_index];

}
Vector2i GameSprite::GetImageSize() const
{
	if (TEX == nullptr)
	{
		return Vector2i();
	}
	return TEX->GetImageSize();
}
Vector2i GameSprite::GetSpriteImageSize(size_t index) const
{
	if(TEX == nullptr)
		return Vector2i();
	if (index >= m_UVMap.size())
	{
		return Vector2i();
	}

	FRect temp = m_UVMap[index];
	Vector2i imageSize = GetImageSize();
	temp.Size.x *= imageSize.x;
	temp.Size.y *= imageSize.y;
	return Vector2i(temp.Size);
}
GameSprite::GameSprite()
{
}


GameSprite::~GameSprite()
{
}
