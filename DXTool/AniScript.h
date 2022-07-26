
#pragma once
#include <ComScript.h>
#include<Camera.h>
#include<RenderParts.h>
class Com2DFrameAni;
class AniScript : public ComScript
{
private:
	SPTR<RenderParts> Parts;
	std::wstring m_SpriteName;
	std::wstring m_SubDataName;
	bool m_bShowAxis;
public:
	void ChangeAni(const wchar_t* AniName);
	void CreateAni(const wchar_t* _AniName, unsigned int _StartFrame, unsigned int _EndFrame, float _FrameTime = 0.1f, bool _bLoop = true);
	void CreateAni(const wchar_t* _AniName, unsigned int _StartFrame, unsigned int _EndFrame, bool _bLoop, float _FrameTime = 0.1f);
	void DeleteAni(const wchar_t* _AniName);
	void Clear();
	SPTR<Com2DFrameAni> GetComFrameAni();
	
	void SpriteSet(const wchar_t* FileName);
	void SubDataSet(const wchar_t* FileName);
	std::wstring GetSpriteName()const
	{
		return m_SpriteName;
	}
	void EventDelete(const wchar_t * AniName, unsigned int _StartFrame, unsigned int _EndFrame);
	void SetPivot(int x, int y);
	void SetAxis(bool isShow)
	{
		m_bShowAxis = isShow;
	}
public:
	bool Init() override;
	void Update() override;
	void LateUpdate() override;
	void DebugRender() override;
public:
	AniScript();
	~AniScript();
};