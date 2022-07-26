#include "TileMapRender.h"
#include"GameSprite.h"
#include"Transform.h"
#include"Level.h"



bool TileMapRender::Init(int _renderGroup)
{
	if (ComRender::Init(_renderGroup) == false)
	{
		return false;
	}
	m_Vertex = ResMgr<VertexShader>::Find(L"VSTexRect");
	m_Pixel = ResMgr<PixelShader>::Find(L"PSTexRect");
	m_Mesh = ResMgr<Mesh>::Find(L"TEXMESH");
	m_Blend = ResMgr<DxBlend>::Find(L"DEFBLEND");

	return true;
}

void TileMapRender::SetSprite(const wchar_t *_SpriteName)
{
	m_Sprite = ResMgr<GameSprite>::Find(_SpriteName);

	if (m_Sprite == nullptr)
	{
		assert(false && L"Fail SetSprite, Not find Sprite");
	}

	m_TileSize.Size = m_Sprite->GetSpriteImageSize(0);
}

size_t TileMapRender::GetTileSetSize() const
{
	return m_Sprite->CutSize();
}

int TileMapRender::GetTileState(const Vector2i & Pos)
{
	Vector2i index = IndexCalc(Pos);
	SPTR<TileInfo> find = MapFindHelper<SPTR<TileInfo>>(m_TileMap, index.i64);

	if (find == nullptr)
	{
		return -1;
	}
	return find->SpriteIndex;
}

TileMapRender::TileMapRender()
{
}


TileMapRender::~TileMapRender()
{
}

void TileMapRender::Render(const Matrix4x4 & _VPMatrix)
{

	SubTransUpdate();

	std::unordered_map<__int64, SPTR<TileInfo>>::iterator StartIter = m_TileMap.begin();
	std::unordered_map<__int64, SPTR<TileInfo>>::iterator EndIter = m_TileMap.end();

	Vector2i index;

	Vector3f size = Vector3f(m_TileSize.Size.x, m_TileSize.Size.y, 1.0f);
	m_ScaleMat.SetScale(size);

	Vector3f pos = Vector3f();

	for (; StartIter != EndIter; ++StartIter)
	{
		index.i64 = StartIter->first; // 키 값이 인덱스값이다.
		pos.x = GetWorldSubPosition().x + (float)index.x * size.x;
		pos.y = GetWorldSubPosition().y + (float)index.y * size.y;
		pos.z = GetWorldSubPosition().z;
		m_ScaleMat.vec3 = pos;

		m_Vertex->UpdateCBuffer<Matrix4x4>(0, (m_ScaleMat * _VPMatrix).ReturnTransPose());
		m_Vertex->UpdateCBuffer<FRect>(1, m_Sprite->CalUV(StartIter->second->SpriteIndex));

		m_Mesh->Update();
		m_Vertex->Update();
		m_Pixel->Update();
		m_Sprite->Update();
		m_Blend->Update();
		m_Mesh->Render();
	}
}

Vector2i TileMapRender::IndexCalc(const Vector2i & _Pos)
{
	float X = (_Pos.x - GetTransform()->GetWorldPosition().x) / m_TileSize.Size.x;
	float Y = (_Pos.y - GetTransform()->GetWorldPosition().y) / m_TileSize.Size.y;

	if (0 < X)
	{
		X += 0.5f;
	}

	if (0 < Y)
	{
		Y += 0.5f;
	}

	if (0 > X)
	{
		X -= 0.5f;
	}

	if (0 > Y)
	{
		Y -= 0.5f;
	}

	return Vector2i((int)X, (int)Y);
}

void TileMapRender::CreateTile(int x, int y, int index)
{
	Vector2i IndexPos = IndexCalc(Vector2i(x,y));
	CreateTile(IndexPos.i64, index);
}

void TileMapRender::CreateTile(const Vector2i& _Pos, int index)
{
	Vector2i IndexPos = IndexCalc(_Pos);
	CreateTile(IndexPos.i64, index);

}
void TileMapRender::CreateTile(const __int64 _Pos, int index)
{
	SPTR<TileInfo> find = MapFindHelper<SPTR<TileInfo>>(m_TileMap, _Pos);

	if (find == nullptr)
	{
		TileInfo* newTile = new TileInfo();
		newTile->SpriteIndex = index;
		m_TileMap.insert(std::unordered_map<__int64, SPTR<TileInfo>>::value_type(_Pos, newTile));
		return;
	}
	find->SpriteIndex = index;
}
void TileMapRender::DeleteTile(int x, int y)
{
	DeleteTile(Vector2i(x, y));
}

void TileMapRender::DeleteTile(const Vector2i& _Pos)
{
	Vector2i IndexPos = IndexCalc(_Pos);

	std::unordered_map<__int64, SPTR<TileInfo>>::iterator find = m_TileMap.find(IndexPos.i64);


	if (find == m_TileMap.end())
	{
		return;
	}
	m_TileMap.erase(find);
}

void TileMapRender::Clear()
{
	m_TileMap.clear();
}

// IO Function.
std::list<TileMapRender::IOTileData> TileMapRender::IOAllData()
{
	std::unordered_map<__int64, SPTR<TileInfo>>::iterator StartIter = m_TileMap.begin();
	std::unordered_map<__int64, SPTR<TileInfo>>::iterator EndIter = m_TileMap.end();

	std::list<TileMapRender::IOTileData> List;

	for (; StartIter != EndIter; ++StartIter)
	{
		TileMapRender::IOTileData Info;

		Info.index = StartIter->first;
		Info.SpriteIndex = StartIter->second->SpriteIndex;
		List.push_back(Info);
	}

	return List;
}
