#include "Actor.h"
#include"Component.h"
#include"Transform.h"
#include"Level.h"

void Actor::SetLevel(Level * level)
{
	ILevelBase::SetLevel(level);

	it_ChildStart = m_ChildList.begin();
	it_ChildEnd = m_ChildList.end();

	for (; it_ChildStart != it_ChildEnd; ++it_ChildStart)
	{
		(*it_ChildStart)->SetLevel(level);
	}
}

void Actor::FixUpdate()
{
	CStartIter = m_ComList.begin();
	CEndIter = m_ComList.end();
	
	for (; CStartIter != CEndIter; ++CStartIter)
	{
		if (true == (*CStartIter)->IsUpdate())
		{
			(*CStartIter)->FixUpdate();
		}
	}

	if (m_ChildList.size() > 0)
	{
		it_ChildStart = m_ChildList.begin();
		it_ChildEnd = m_ChildList.end();

		for (; it_ChildStart != it_ChildEnd; ++it_ChildStart)
		{
			if (true == (*it_ChildStart)->IsUpdate())
			{
				(*it_ChildStart)->FixUpdate();
			}
		}
	}
}

void Actor::Update()
{
	CStartIter = m_ComList.begin();
	CEndIter = m_ComList.end();

	for (; CStartIter != CEndIter; ++CStartIter)
	{
		if (true == (*CStartIter)->IsUpdate())
		{
			(*CStartIter)->Update();
		}
	}
	it_ChildStart = m_ChildList.begin();
	it_ChildEnd = m_ChildList.end();

	for (; it_ChildStart != it_ChildEnd; ++it_ChildStart)
	{
		if (true == (*it_ChildStart)->IsUpdate())
		{
			(*it_ChildStart)->Update();
		}
	}
}

void Actor::LateUpdate()
{
	CStartIter = m_ComList.begin();
	CEndIter = m_ComList.end();

	for (; CStartIter != CEndIter; ++CStartIter)
	{
		if (true == (*CStartIter)->IsUpdate())
		{
			(*CStartIter)->LateUpdate();
		}
	}
	it_ChildStart = m_ChildList.begin();
	it_ChildEnd = m_ChildList.end();

	for (; it_ChildStart != it_ChildEnd; ++it_ChildStart)
	{
		if (true == (*it_ChildStart)->IsUpdate())
		{
			(*it_ChildStart)->LateUpdate();
		}
	}
}
void Actor::EndUpdate()
{
	CStartIter = m_ComList.begin();
	CEndIter = m_ComList.end();

	for (; CStartIter != CEndIter; ++CStartIter)
	{
		if (true == (*CStartIter)->IsUpdate())
		{
			(*CStartIter)->EndUpdate();
		}
	}
	it_ChildStart = m_ChildList.begin();
	it_ChildEnd = m_ChildList.end();

	for (; it_ChildStart != it_ChildEnd; ++it_ChildStart)
	{
		if (true == (*it_ChildStart)->IsUpdate())
		{
			(*it_ChildStart)->EndUpdate();
		}
	}
}

void Actor::FinalUpdate()
{
	CStartIter = m_ComList.begin();
	CEndIter = m_ComList.end();

	for (; CStartIter != CEndIter; ++CStartIter)
	{
		if (true == (*CStartIter)->IsUpdate())
		{
			(*CStartIter)->FinalUpdate();
		}
	}
	it_ChildStart = m_ChildList.begin();
	it_ChildEnd = m_ChildList.end();

	for (; it_ChildStart != it_ChildEnd; ++it_ChildStart)
	{
		if (true == (*it_ChildStart)->IsUpdate())
		{
			(*it_ChildStart)->FinalUpdate();
		}
	}
}

void Actor::DebugRender()
{
	CStartIter = m_ComList.begin();
	CEndIter = m_ComList.end();

	for (; CStartIter != CEndIter; ++CStartIter)
	{
		if (true == (*CStartIter)->IsUpdate())
		{
			(*CStartIter)->DebugRender();
		}
	}
	it_ChildStart = m_ChildList.begin();
	it_ChildEnd = m_ChildList.end();

	for (; it_ChildStart != it_ChildEnd; ++it_ChildStart)
	{
		if (true == (*it_ChildStart)->IsUpdate())
		{
			(*it_ChildStart)->DebugRender();
		}
	}
}

void Actor::SetTransform(Transform * trans)
{
	m_Trans = trans;
}

Transform * Actor::GetTransform() const
{
	return m_Trans;
}

void Actor::SetParent(SPTR<Actor> _Parent)
{
	m_Parent = _Parent.Get();
}

void Actor::ChildCheckProcess()
{
	if (m_Parent == nullptr)
	{
		return;
	}
	if (m_Parent->IsDeath())
	{
		this->Death();
		return;
	}
	m_Parent->m_ChildList.push_back(this);

	GetTransform()->SetWorldPosition(GetTransform()->GetWorldPosition());
	GetTransform()->SetWorldScale(GetTransform()->GetWorldScale());

}
void Actor::SetUpdate(bool isUpdate)
{
	std::list<SPTR<Component>>::iterator ComStartIter = m_ComList.begin();
	std::list<SPTR<Component>>::iterator ComEndIter = m_ComList.end();

	for (; ComStartIter != ComEndIter; ++ComStartIter)
	{
		(*ComStartIter)->SetUpdate(isUpdate);
	}

	std::list<SPTR<Actor>>::iterator ChildStartIter = m_ChildList.begin();
	std::list<SPTR<Actor>>::iterator ChildEndIter = m_ChildList.end();

	for (; ChildStartIter != ChildEndIter; ++ChildStartIter)
	{
		(*ChildStartIter)->SetUpdate(isUpdate);
	}

	IUpdate::SetUpdate(isUpdate);
}
void Actor::Death()
{
	std::list<SPTR<Component>>::iterator ComStartIter = m_ComList.begin();
	std::list<SPTR<Component>>::iterator ComEndIter = m_ComList.end();

	for (; ComStartIter != ComEndIter; ++ComStartIter)
	{
		(*ComStartIter)->SetActor(nullptr);
		(*ComStartIter)->Death();
	}

	std::list<SPTR<Actor>>::iterator ChildStartIter = m_ChildList.begin();
	std::list<SPTR<Actor>>::iterator ChildEndIter = m_ChildList.end();

	for (; ChildStartIter != ChildEndIter; ++ChildStartIter)
	{
		(*ChildStartIter)->m_Parent = nullptr;
		(*ChildStartIter)->Death();
	}

	IUpdate::Death();
}
void Actor::OverActor(std::list<std::wstring>* list, const wchar_t * levelName)
{
	list->push_back(levelName);

	GetLevel()->OverActorPush(this, (*list));

	m_bOver = true;
	if (list != nullptr)
	{
		delete list;
	}
}
Actor::Actor() : m_Trans(nullptr), m_Order(0), m_bOver(false)
{
}


Actor::~Actor()
{
}
