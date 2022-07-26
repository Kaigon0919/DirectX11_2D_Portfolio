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
	virtual bool Loading()override;// 씬이 로딩되지 않았을때 한번만 실행
	virtual void Start()override {} // 씬이 체인지 되었을때 한번 실행
	virtual void Update()override; // 모든 액터의 업데이트가 실행되기 전에 한번실행
	virtual void LateUpdate()override {} // 모든 액터의 업데이트가 끝나고 한번 실행
	virtual void End()override {} // 내가 실행중인데 다른씬으로 변경되었을때 한번 실행
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

