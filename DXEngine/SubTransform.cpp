#include "SubTransform.h"
#include"Transform.h"


Vector3f SubTransform::GetWorldSubPosition() const
{
	if (m_SubData == nullptr)
	{
		return GetTransform()->GetWorldPosition();
	}
	return m_SubData->m_Pivot + GetTransform()->GetWorldPosition();
}

void SubTransform::SetWorldSubPosition(const Vector3f & value)
{
	if (m_SubData == nullptr)
	{
		m_SubData = new SubTransData();
	}
	m_SubData->m_Pivot = value - GetTransform()->GetWorldPosition();
}

const Matrix4x4 & SubTransform::GetSubWorldMat() const
{
	if (nullptr == m_SubData)
	{
		return GetTransform()->GetWorldMartix();
	}
	return m_SubData->m_WorldMat;
}

void SubTransform::SubTransUpdate()
{
	if (m_SubData == nullptr)
	{
		// SubTrans를 사용하는 컴포넌트는 Matrix를 받을때 SubData가 없으면 Transform 월드를 반환한다.
		return;
	}
	if (GetTransform() == nullptr)
	{
		return;
	}

	m_SubData->m_ScaleMat.SetScale(m_SubData->m_Scale);
	m_SubData->m_RotMat.SetRotationDegree(m_SubData->m_Rotate);
	m_SubData->m_PosMat.SetPosition(m_SubData->m_Pivot + GetTransform()->GetWorldPosition());
	m_SubData->m_RevolveMat.SetRotation(m_SubData->m_Revolve);
	m_SubData->m_WorldMat = m_SubData->m_ScaleMat * m_SubData->m_RotMat * m_SubData->m_PosMat * m_SubData->m_RevolveMat;

}

SubTransform::SubTransform() : m_SubData(nullptr)
{
}


SubTransform::~SubTransform()
{
	if (m_SubData)
	{
		delete m_SubData;
		m_SubData = nullptr;
	}
}

Vector3f SubTransform::GetLocalSubPosition() const
{
	if (m_SubData == nullptr)
	{
		return GetTransform()->GetLocalPosition();
	}
	return m_SubData->m_Pivot;
}


Vector3f SubTransform::GetLocalSubRotate() const
{
	if (m_SubData == nullptr)
	{
		return GetTransform()->GetLocalRotate();
	}
	return m_SubData->m_Rotate;
}

Vector3f SubTransform::GetLocalSubScale() const
{
	if (m_SubData == nullptr)
	{
		return GetTransform()->GetLocalScale();
	}
	return m_SubData->m_Scale;
}

Vector2f SubTransform::GetLocal2DSubPosition() const
{
	if (m_SubData == nullptr)
	{
		return GetTransform()->GetLocal2DPosition();
	}
	return Vector2f(m_SubData->m_Pivot.x, m_SubData->m_Pivot.x);
}
Vector2f SubTransform::GetLocal2DSubScale() const
{
	if (m_SubData == nullptr)
	{
		return GetTransform()->GetLocal2DScale();
	}
	return Vector2f(m_SubData->m_Scale.x, m_SubData->m_Scale.x);
}

Vector2f SubTransform::GetWorld2DSubPosition() const
{
	if (m_SubData == nullptr)
	{
		return GetTransform()->GetWorld2DPosition();
	}
	Vector3f returnValue = m_SubData->m_Pivot + GetTransform()->GetWorldPosition();
	return Vector2f(returnValue.x, returnValue.y);
}

Vector2f SubTransform::GetWorld2DSubScale() const
{
	if (m_SubData == nullptr)
	{
		return GetTransform()->GetWorld2DScale();
	}
	Vector3f returnValue = m_SubData->m_Scale * GetTransform()->GetWorldScale();
	return Vector2f(returnValue.x, returnValue.y);
}
