#include "Component.h"
#include"Actor.h"

Transform * Component::GetTransform() const
{
	if (GetActor() == nullptr)
	{
		return nullptr;
	}

	return GetActor()->GetTransform();
}

bool Component::IsMultiCheck(Actor * _Actor)
{
	return true;
}

bool Component::IsUpdate() const
{
	return IUpdate::IsUpdate() && GetActor()->IsUpdate();
}

bool Component::IsDeath() const
{
	if (GetActor() == nullptr)
	{
		return true;
	}
	return IUpdate::IsDeath() || GetActor()->IsDeath();
}

