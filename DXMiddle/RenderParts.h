#pragma once
#include<ComScript.h>
#include<Com2DFrameAni.h>

class Render2DSprite;
class RenderParts : public ComScript
{
public:
	enum eRednerParts
	{
		RP_Skin = 0,
		RP_Hair = 1,
		RP_ShoesA = 2,
		RP_ShoesB = 3,
		RP_PantsA = 4,
		RP_PantsB = 5,
		RP_Coat = 6,
		RP_WeaponA = 7,
		RP_WeaponB = 8,
		RP_Max
	};
private:
	SPTR<Transform> m_Trans;
	SPTR<Render2DSprite> m_Render[RP_Max];
	SPTR<Com2DFrameAni> m_FrameAni[RP_Max];

	Vector2i PartSubTrans[RP_Max][210];
	Vector2i Pivot;
	Vector3f SubPos;
public:
	bool Init();

	void FixUpdate()override;
	void Update() override;
	void LateUpdate() override;
	void EndUpdate() override;
	void DebugRender() override;
public:
	void SetPivot(const Vector2i& pivot);
	void SettingPart(eRednerParts PartNumber, const wchar_t * SpriteName, const wchar_t *DataName);
	void PivotUpdate(eRednerParts PartNumber);
	void SetSprite(eRednerParts PartNumber, const wchar_t * SpriteName);
	void DeletePart(eRednerParts PartNumber);
	void DeleteAllPart();
	void LoadSubData(eRednerParts PartNumber, const wchar_t * fileName);
	void SetPos(const Vector3f& pos);

	void ChangeAni(const wchar_t* AniName);
	void CreateAni(const wchar_t * _AniName, unsigned int _StartFrame, unsigned int _EndFrame, float _FrameTime = 0.1f, bool _bLoop = true);
	void CreateAni(const wchar_t * _AniName, unsigned int _StartFrame, unsigned int _EndFrame, bool _bLoop, float _FrameTime = 0.1f);
	void DeleteAni(const wchar_t* _AniName);
	void AniClear();

	void AniOff();
	void AniOn();

	template<class T>
	void SetFrameEvent(const wchar_t* _AniName, unsigned int _StartFrame, unsigned int _EndFrame, void(T::*pFunc)(void*), T* _Obj, void* m_EventData = nullptr, Com2DFrameAni::EVENTTYPE _eType = Com2DFrameAni::CHANGEEND)
	{
		m_FrameAni[RP_Skin]->SetFrameEvent(_AniName, _StartFrame, _EndFrame, pFunc, _Obj, m_EventData, _eType);
	}
	void EventDelete(const wchar_t * _AniName, int idx);
	int FindEventIndex(const wchar_t * AniName, unsigned int _StartFrame, unsigned int _EndFrame);

	bool IsCurAniName(std::wstring AniName);
	bool IsAniEnd()const;
	float CurAniPer();

	SPTR<Com2DFrameAni> GetComFrameAni();
public:
	RenderParts();
	~RenderParts();
};