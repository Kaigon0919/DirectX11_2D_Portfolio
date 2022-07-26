#pragma once
#include<ComScript.h>

class TileMapRender;
class Render2DSprite;
class Fade;
class BackGround :public ComScript
{
private:
	SPTR<TileMapRender> m_TileMap;
	SPTR<Render2DSprite> m_Render;
	std::list<SPTR<Actor>> m_Warps;
	std::list<SPTR<Actor>> m_Objs;

	std::wstring m_SoundName;
public:
	bool Init() override;
	void Update() override;
public:
	void DataLoad(const wchar_t* FileName);
private:
	void CreateGate(int Mode, Vector2f Pos, Vector2f Scale, const wchar_t* NextLevel, Vector2f NextPos);
	void CreateObject(Vector2f Pos, const wchar_t* SpriteName);
public:
	void CloseGate();
	void OpenGate();
	void SetFade(SPTR<Fade> fade);
public:
	BackGround();
	~BackGround();
};

