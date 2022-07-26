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
	virtual bool Loading()override;// ���� �ε����� �ʾ����� �ѹ��� ����
	virtual void Start()override {} // ���� ü���� �Ǿ����� �ѹ� ����
	virtual void Update()override; // ��� ������ ������Ʈ�� ����Ǳ� ���� �ѹ�����
	virtual void LateUpdate()override {} // ��� ������ ������Ʈ�� ������ �ѹ� ����
	virtual void End()override {} // ���� �������ε� �ٸ������� ����Ǿ����� �ѹ� ����
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

