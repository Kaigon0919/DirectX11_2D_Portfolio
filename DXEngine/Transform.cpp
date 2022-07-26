#include "Transform.h"
#include"Actor.h"


bool Transform::IsMultiCheck(Actor * _Actor)
{
	if (_Actor->GetComponent<Transform>() != nullptr)
	{
		return false;
	}
	return true;
}


void Transform::SetWorldScale(float _x, float _y, float _z)
{
	SetWorldScale(Vector3f(_x, _y, _z));
}

void Transform::SetWorldScale(const Vector3f & ref)
{
	if (GetActor()->GetParent() != nullptr)
	{
		m_LocalScale = ref / GetActor()->GetParent()->GetTransform()->GetWorldScale();
		CalWorldScale();
	}
	else
	{
		m_WorldScale =  m_LocalScale = ref;
	}
	m_UpdateGeo |= TRANSUPDATE_SCALE;
}

void Transform::SetWorldRotate(float _x, float _y, float _z)
{
	SetWorldRotate(Vector3f(_x, _y, _z));
}

void Transform::SetWorldRotate(const Vector3f & ref)
{

	if (GetActor()->GetParent() != nullptr)
	{
		m_LocalRot = ref / GetActor()->GetParent()->GetTransform()->GetWorldScale();
		CalWorldRotate();
	}
	else
	{
		m_WorldRot = m_LocalRot = ref;
	}
	m_UpdateGeo |= TRANSUPDATE_ROTATE;
}

void Transform::SetWorldPosition(float _x, float _y, float _z)
{
	SetWorldPosition(Vector3f(_x, _y, _z));
}

void Transform::SetWorldPosition(const Vector3f & ref)
{
	if (GetActor()->GetParent() != nullptr)
	{
		SPTR<Transform> ParentTrans = GetActor()->GetParent()->GetTransform();
		m_LocalPos = (ref - ParentTrans->GetWorldPosition()) / ParentTrans->GetWorldScale();
		CalWorldPosition();
	}
	else
	{
		m_WorldPos = m_LocalPos = ref;
	}
	m_UpdateGeo |= TRANSUPDATE_POSITION;
}

const Matrix4x4 Transform::GetParentMatrix() const
{
	if (GetActor()->GetParent() == nullptr)
	{
		Matrix4x4 temp;
		temp.Identity();
		return temp;
	}
	return GetActor()->GetParent()->GetTransform()->GetWorldMartix();
}

bool Transform::Init()
{
	if (GetActor()->GetTransform())
	{
		assert(false && L"Transform already exists.");
		return false;
	}

	GetActor()->SetTransform(this);
	return true;
}

void Transform::EndUpdate()
{
	if (m_UpdateGeo & TRANSUPDATE_SCALE)
	{
		m_ScaleMat.SetScale(m_LocalScale);
		m_bWorldUpdate = true;
	}
	if (m_UpdateGeo & TRANSUPDATE_ROTATE)
	{
		m_RotMat.SetRotationDegree(m_LocalRot);
		m_bWorldUpdate = true;
	}
	if (m_UpdateGeo & TRANSUPDATE_POSITION)
	{
		m_PosMat.SetPosition(m_LocalPos);
		m_bWorldUpdate = true;
	}
	if (m_UpdateGeo & TRANSUPDATE_REVOLVE)
	{
		m_RevolveMat.SetRotationDegree(m_Revolve);
		m_bWorldUpdate = true;
	}

	if (GetActor()->GetParent() == nullptr && m_bWorldUpdate == true)
	{
		m_World = m_ScaleMat * m_RotMat * m_PosMat * m_RevolveMat;
	}
	else if ((GetActor()->GetParent() != nullptr && GetActor()->GetParent()->GetTransform()->m_bWorldUpdate == true) || m_bWorldUpdate == true)
	{
		m_bWorldUpdate = true;
		m_World = m_ScaleMat * m_RotMat * m_PosMat * m_RevolveMat * GetActor()->GetParent()->GetTransform()->GetWorldMartix();
		CalWorldPosition();
		CalWorldRotate();
		CalWorldScale();
	}

	m_UpdateGeo = 0;
}

void Transform::FinalUpdate()
{
	m_bWorldUpdate = false;
}

void Transform::CalWorldScale()
{
	if (GetActor()->GetParent() != nullptr)
	{
		m_WorldScale = m_LocalScale * GetActor()->GetParent()->GetTransform()->GetWorldScale();
	}
	else
	{
		m_WorldScale = m_LocalScale;
	}
}

void Transform::CalWorldRotate()
{
	if (GetActor()->GetParent() != nullptr)
	{
		m_WorldRot = m_LocalRot * GetActor()->GetParent()->GetTransform()->GetWorldRotate();
	}
	else
	{
		m_WorldRot = m_LocalRot;
	}
}

void Transform::CalWorldPosition()
{
	if (GetActor()->GetParent() != nullptr)
	{
		SPTR<Transform> ParentTrans = GetActor()->GetParent()->GetTransform();
		m_WorldPos = (m_LocalPos * ParentTrans->GetWorldScale()) + ParentTrans->GetWorldPosition();
	}
	else
	{
		m_WorldPos = m_LocalPos;
	}
}

Transform::Transform() : m_LocalPos(), m_LocalRot(),m_LocalScale(Vector3f::One) , m_WorldPos(m_LocalPos), m_WorldRot(m_LocalRot), m_WorldScale(m_LocalScale)
{
}


Transform::~Transform()
{
}
