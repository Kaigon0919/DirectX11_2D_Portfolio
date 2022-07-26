#pragma once
#include "ComRender.h"
#include "IRefCount.h"
#include<unordered_map>
class TileMapRender : public ComRender
{
private:
	SPTR<VertexShader> m_Vertex;
	SPTR<PixelShader> m_Pixel;
	SPTR<Mesh> m_Mesh;
	SPTR<GameSprite> m_Sprite;
	SPTR<DxBlend> m_Blend;
private:
	struct TileInfo : public IRefCount
	{
		int SpriteIndex;
	};

public:
	std::unordered_map<__int64, SPTR<TileInfo>> m_TileMap;
	FRect m_TileSize;
	Matrix4x4 m_ScaleMat;

public:
	bool Init(int _renderGroup = 1) override;
	void SetTileSize(Vector2f size)
	{
		m_TileSize.Size = size;
	}
	Vector2f GetTileSize()const
	{
		return m_TileSize.Size;
	}
	void SetSprite(const wchar_t *_SpriteName);

	size_t GetTileSetSize() const;

	int GetTileState(const Vector2i& Pos);

	// ComRender을(를) 통해 상속됨
	virtual void Render(const Matrix4x4 & _VPMatrix) override;

	Vector2i IndexCalc(const Vector2i& _Pos);
public:
	void CreateTile(int x, int y, int index);
	void CreateTile(const Vector2i& _Pos, int index);
	void CreateTile(const __int64 _Pos, int index);
	void DeleteTile(int x, int y);
	void DeleteTile(const Vector2i& _Pos);
	void Clear();

// IO Data, Function.
public:
	struct IOTileData
	{
	public:
		__int64 index;
		int SpriteIndex;
	};
	std::list<IOTileData> IOAllData();


public:
	TileMapRender();
	~TileMapRender();

};

