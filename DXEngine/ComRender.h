#pragma once
#include"SubTransform.h"
#include"VectorData.h"

#include"VertexShader.h"
#include"PixelShader.h"
#include"Mesh.h"
#include"GameSprite.h"
#include"DxBlend.h"

class ComRender : public SubTransform
{
private:
	friend class RenderMgr;
private:
	int m_RenderGroup;

protected:
	virtual bool Init(int _renderGroup = 1);
private:
	virtual void Render(const Matrix4x4& _VPMatrix) = 0;
public:
	ComRender();
	~ComRender();
};

