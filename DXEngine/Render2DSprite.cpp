#include "Render2DSprite.h"
#include"Actor.h"
#include"Level.h"
#include"VertexShader.h"
#include"PixelShader.h"
#include"Mesh.h"
#include"GameSprite.h"
#include"DxBlend.h"
#include"Transform.h"
bool Render2DSprite::Init(int _order)
{
	if (ComRender::Init(_order) == false)
	{
		return false;
	}

	m_Vertex = ResMgr<VertexShader>::Find(L"VSTexRect");
	m_Pixel = ResMgr<PixelShader>::Find(L"PSTexRect");
	m_Mesh = ResMgr<Mesh>::Find(L"TEXMESH");
	m_Blend = ResMgr<DxBlend>::Find(L"DEFBLEND");
	return true;
}

void Render2DSprite::Render(const Matrix4x4 & _VP)
{
	if (nullptr == m_Sprite)
	{
		return;
	}

	SubTransUpdate();

	Matrix4x4 WVP = GetSubWorldMat() * _VP;
	WVP.TransPose();

	FRect CalUV;
	if (m_bCut)
	{
		CalUV = m_Sprite->CalUV(m_Index);
	}
	else
	{
		CalUV.Position = Vector2f();
		CalUV.Size = Vector2f(1.0f,1.0f);
	}

	m_Vertex->UpdateCBuffer<Matrix4x4>(0, WVP);
	m_Vertex->UpdateCBuffer<FRect>(1, CalUV);
	m_Pixel->UpdateCBuffer<Color4f>(0, TransColor);
	m_Pixel->UpdateCBuffer<TexRenderOption>(1, option);
	m_Mesh->Update();
	m_Vertex->Update();
	m_Pixel->Update();
	if (m_Sprite != nullptr)
	{
		m_Sprite->Update();
	}
	m_Blend->Update();
	m_Mesh->Render();
}

void Render2DSprite::SetSprite(const wchar_t * _SpriteName, size_t _index)
{
	m_Index = _index;
	m_Sprite = ResMgr<GameSprite>::Find(_SpriteName);
	if (m_Sprite == nullptr)
	{
		assert(false && L"Fail SetSprite, Not find Sprite");
	}
}

void Render2DSprite::SetSpriteIndex(const size_t _index)
{
	if (m_Sprite->CutSize() <= _index)
	{
		return;
	}
	m_Index = _index;
}

Vector2i Render2DSprite::GetImageSIze() const
{
	if (m_Sprite == nullptr)
	{
		return Vector2i();
	}
	return m_Sprite->GetImageSize();
}
Vector2i Render2DSprite::GetSpriteImageSize(const size_t index) const
{
	if (m_Sprite == nullptr)
	{
		return Vector2i();
	}
	return m_Sprite->GetSpriteImageSize(index);
}
void Render2DSprite::SetCutShow(bool isCut)
{
	m_bCut = isCut;
}
void Render2DSprite::SetTransColor(const Color4f & color)
{
	TransColor = color;
}
Render2DSprite::Render2DSprite() : m_bCut(true) , TransColor(0.0f, 0.0f, 0.0f, 0.0f) , option{1.0f, 0,}
{
}


Render2DSprite::~Render2DSprite()
{
}
