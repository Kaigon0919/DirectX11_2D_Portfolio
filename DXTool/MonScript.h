#pragma once
#include<Level.h>
#include<SaveAndLoadData.h>
#include<list>

enum MonType
{
	Mon_Goblin0,
	Mon_Goblin1,
	Mon_Tau,
	Mon_Max
};
class TileMapRender;
class Render2DSprite;
class MonScript : public Level::LevelScript
{
private:
	SPTR<Actor> m_CameraActor;
private:
	std::list<SPTR<Actor>> m_MonList;
	std::unordered_map<Actor*, MonData> m_MonMap;

	SPTR<Render2DSprite> m_BackGround;
	SPTR<TileMapRender> m_TileMap;
	std::list<SPTR<Actor>> m_GateList;
	std::list<SPTR<Actor>> m_ObjList;

	int m_Type;
public:
	virtual bool Init()override;
	virtual bool Loading()override;// 씬이 로딩되지 않았을때 한번만 실행
	virtual void Start()override {} // 씬이 체인지 되었을때 한번 실행
	virtual void Update()override; // 모든 액터의 업데이트가 실행되기 전에 한번실행
	virtual void LateUpdate()override {} // 모든 액터의 업데이트가 끝나고 한번 실행
	virtual void End()override {} // 내가 실행중인데 다른씬으로 변경되었을때 한번 실행
	virtual void DebugRender()override;
public:
	void Save();
	void Load();
	void Clear();
	void SpriteLoad();
	void SetType(int number)
	{
		m_Type = number;
	}
private:
	void CreateMon(int type, Vector2f Pos);
	void CreateGate(int Mode, Vector2f Pos, Vector2f Scale, const wchar_t * NextLevel, Vector2f NextPos);
	void CreateObject(Vector2f Pos, const wchar_t * SpirteName);
private:
	std::wstring m_SpriteName;
public:
	MonScript();
	~MonScript();
};

