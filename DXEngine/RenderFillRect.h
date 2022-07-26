#pragma once
#include "ComRender.h"

class RenderFillRect : public ComRender
{
public:
	friend class Actor;
private:
	SPTR<VertexShader> m_Vertex;
	SPTR<PixelShader> m_Pixel;
	SPTR<Mesh> m_Mesh;
	SPTR<DxBlend> m_Blend;
private:
	Color4f FillColor;
	Color4f MulColor;
private:
	virtual bool Init(int _order = 1) override;
	virtual void Render(const Matrix4x4& ref) override;
public:
	void SetFillColor(const Color4f& color)
	{
		FillColor = color;
	}
	void SetMulColor(const Color4f& mulColor)
	{
		MulColor = mulColor;
	}
public:
	RenderFillRect();
	~RenderFillRect();
};

