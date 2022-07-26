#pragma once
#include "ComRender.h"
#include"RenderData.h"
class Render2DSprite : public ComRender
{
public:
	friend class Actor;
private:
	SPTR<VertexShader> m_Vertex;
	SPTR<PixelShader> m_Pixel;
	SPTR<Mesh> m_Mesh;
	SPTR<GameSprite> m_Sprite;
	SPTR<DxBlend> m_Blend;

private:
	Color4f TransColor;
	TexRenderOption option;
	size_t m_Index;
	bool m_bCut;


private:
	virtual bool Init(int _order = 1) override;
	virtual void Render(const Matrix4x4& ref) override;

public:
	void SetSprite(const wchar_t * _SpriteName, size_t _index = 0);
	void SetSpriteIndex(const size_t _index);
	Vector2i GetImageSIze()const;
	Vector2i GetSpriteImageSize(const size_t index)const;
	void SetCutShow(bool isCut);
	void SetTransColor(const Color4f& color);
	void SetFillMode(int Mode)
	{
		option.dir = Mode;
	}
	void SeFillMode(int Mode, float value)
	{
		option.dir = Mode;
		if (value < 0.0f) value = 0.0f;
		if (value > 1.0f) value = 1.0f;
		option.fill = value;
	}
	void SetFill(float value)
	{
		if (value < 0.0f) value = 0.0f;
		if (value > 1.0f) value = 1.0f;
		option.fill = value;
	}
public:
	Render2DSprite();
	~Render2DSprite();
};

