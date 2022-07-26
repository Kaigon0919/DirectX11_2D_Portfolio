#pragma once
#include<Level.h>
#include<SaveAndLoadData.h>

class Render2DSprite;
class TileMapRender;
class MapDlgScript : public Level::LevelScript
{
private:
	SPTR<TileMapRender> m_MapRender;
	SPTR<Render2DSprite> m_SpriteRender;
	SPTR<Actor> m_CameraActor;
	std::wstring m_SpriteName;
	int m_Mode;
	int SelectTile;
	bool isCheck;
private:
	std::list<SPTR<Actor>> m_GateList;
	std::unordered_map<Actor*, GateData> m_GateMap;
	std::list<SPTR<Actor>> m_ObjectList;
	std::unordered_map<Actor*, ObjectData> m_ObjectMap;
public:
	std::wstring inputSpriteName;
	std::wstring ObjectSpriteName;
public:
	virtual bool Init()override;
	virtual bool Loading()override;// ���� �ε����� �ʾ����� �ѹ��� ����
	virtual void Start()override {} // ���� ü���� �Ǿ����� �ѹ� ����
	virtual void Update()override; // ��� ������ ������Ʈ�� ����Ǳ� ���� �ѹ�����
	virtual void LateUpdate()override {} // ��� ������ ������Ʈ�� ������ �ѹ� ����
	virtual void End()override {} // ���� �������ε� �ٸ������� ����Ǿ����� �ѹ� ����
	virtual void DebugRender()override;

public:
	void SetMode(int mode)
	{
		m_Mode = mode;
	}
	void SetTileIndex(int idx)
	{
		SelectTile = idx;
	}
	size_t GetTileCutSize()const;
	void MapSave();
	void MapLoad();
private:
	void SpriteCheck();
	void SpriteSetting(const wchar_t* sprite);
public:
	std::wstring GetSpriteName()const
	{
		return m_SpriteName;
	}
	size_t GetGateSize()const;
	void CreateGate(int Mode, Vector2f Pos, Vector2f Scale, const wchar_t* NextLevel, Vector2f NextPos);
	void DeleteGate(int index);
	GateData GetGateData(int index);

	void CreateObject(Vector2f Pos, const wchar_t * SpirteName);
	void DeleteObject(int index);
	void ObjectClear();
	size_t GetObjSIze()const;
	ObjectData GetObjData(int index);
	void CheckOn()
	{
		isCheck = true;
	}
public:
	MapDlgScript();
	~MapDlgScript();
};

