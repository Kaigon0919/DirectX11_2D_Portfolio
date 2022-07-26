#pragma once
#include<Component.h>
#include<vector>
#include"Timehelper.h"

class Render2DSprite;
class DamageNumber : public Component
{
private:
	size_t m_Value;
	size_t NumberCount;
	std::wstring SpriteName;
	std::vector<SPTR<Render2DSprite>> m_VecRender;
	std::vector<int> m_VecValue;
	Timehelper time_delete;
	Vector3f velocity;
public:
	inline void SetValue(size_t value)
	{
		m_Value = value;
	}
	inline void SetVelocity(Vector3f vel)
	{
		velocity = vel;
	}
public:
	void InitSetting(size_t numberCount, const wchar_t* spriteName, int damage);
	virtual void Update() override;
	void ValueToRenderUpdate();

	

public:
	DamageNumber();
	~DamageNumber();
};

