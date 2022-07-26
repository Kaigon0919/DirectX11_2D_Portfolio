#pragma once
#include "Component.h"
class SubTransform : public Component
{
private:
	struct SubTransData
	{
	public:
		Vector3f m_Pivot;
		Vector3f m_Scale;
		Vector3f m_Rotate;
		Vector3f m_Revolve;

		Matrix4x4 m_ScaleMat;
		Matrix4x4 m_RotMat;
		Matrix4x4 m_PosMat;
		Matrix4x4 m_RevolveMat;

		Matrix4x4 m_WorldMat;
		Matrix4x4 m_ParentMat;
		SubTransData()
		{
			m_Scale = Vector3f::One;
		}
	};
private:
	SubTransData * m_SubData;

public:
	bool IsSub()
	{
		if (m_SubData == nullptr)
		{
			return false;
		}
		return true;
	}

	Vector3f GetLocalSubPosition()const;
	Vector3f GetLocalSubRotate()const;
	

	Vector3f GetLocalSubScale()const;
	Vector3f GetLocalSubRevolve()const
	{
		if (m_SubData == nullptr)
		{
			return Vector3f::Zero;
		}
		return m_SubData->m_Revolve;
	}


	Vector3f GetWorldSubPosition()const;


	Vector2f GetLocal2DSubPosition()const;
	Vector2f GetLocal2DSubScale()const;
	Vector2f GetWorld2DSubPosition()const;
	Vector2f GetWorld2DSubScale()const;
	void SetLocalSubPosition(const Vector3f& value) 
	{
		if (m_SubData == nullptr)
		{
			m_SubData = new SubTransData();
		}
		m_SubData->m_Pivot = value;
	}
	void SetLocalSubRotate(const Vector3f& value) 
	{
		if (m_SubData == nullptr)
		{
			m_SubData = new SubTransData();
		}
		m_SubData->m_Rotate = value;

	}
	void SetLocalSubScale(const Vector3f& value) 
	{
		if (m_SubData == nullptr)
		{
			m_SubData = new SubTransData();
		}
		m_SubData->m_Scale = value;

	}
	void SetLocalSubRevolve(const Vector3f& value) 
	{
		if (m_SubData == nullptr)
		{
			m_SubData = new SubTransData();
		}
		m_SubData->m_Revolve = value;
	}
	void SetWorldSubPosition(const Vector3f& value);
	
	const Matrix4x4& GetSubWorldMat() const;

protected:
	void SubTransUpdate();


public:
	SubTransform();
	~SubTransform();
};

