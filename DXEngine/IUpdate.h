#pragma once
class IUpdate
{
private:
	bool isUpdate;
	bool isDeath;

public:
	virtual inline bool IsUpdate() const
	{
		return isUpdate && !isDeath;
	}

	inline virtual void SetUpdate(bool isOn)
	{
		isUpdate = isOn;
	}
	inline virtual void Death()
	{
		isDeath = true;
	}
	virtual bool IsDeath()const
	{
		return isDeath;
	}

public:
	virtual bool Init() { return true; }
	virtual void FixUpdate() {}
	virtual void Update() {}
	virtual void LateUpdate() {}
	virtual void EndUpdate() {}
	virtual void DebugRender() {}
	virtual void FinalUpdate() {}

public:
	IUpdate() : isUpdate(true), isDeath(false) {}
	virtual ~IUpdate() = 0 {};
};

