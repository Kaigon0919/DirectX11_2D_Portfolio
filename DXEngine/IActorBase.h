#pragma once

class Actor;
class IActorBase
{
private:
	friend Actor;
	Actor * m_Actor;

public:
	inline Actor * GetActor() const
	{
		return m_Actor;
	}
private:
	inline void SetActor(Actor * pLevel)
	{
		m_Actor = pLevel;
	}

public:
	IActorBase() {}
	virtual ~IActorBase() = 0 {}
};

