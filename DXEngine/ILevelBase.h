#pragma once


class Level;
class ILevelBase
{
private:
	friend Level;
	Level * m_Level;

public:
	inline Level * GetLevel() const
	{
		return m_Level;
	}
protected:
	inline virtual void SetLevel(Level * pLevel)
	{
		m_Level = pLevel;
	}

public:
	ILevelBase() : m_Level(nullptr) {}
	virtual ~ILevelBase() = 0 {}
};

