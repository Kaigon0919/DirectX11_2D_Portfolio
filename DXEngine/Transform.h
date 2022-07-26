#pragma once
#include"Component.h"
#include"VectorData.h"

class Transform : public Component
{
private:
	enum TRANSUPDATETYPE
	{
		TRANSUPDATE_SCALE = 0b00000000000000000000000000000001,
		TRANSUPDATE_ROTATE = 0b00000000000000000000000000000010,
		TRANSUPDATE_POSITION = 0b00000000000000000000000000000100,
		TRANSUPDATE_REVOLVE = 0b00000000000000000000000000001000,
	};
public:
	static bool IsMultiCheck(Actor* _Actor);

private:

	bool m_bWorldUpdate;
	int m_UpdateGeo;

	Vector3f m_LocalScale;
	Vector3f m_LocalRot;
	Vector3f m_LocalPos;
	Vector3f m_Revolve;

	Vector3f m_WorldScale;
	Vector3f m_WorldRot;
	Vector3f m_WorldPos;


	Matrix4x4 m_ScaleMat;
	Matrix4x4 m_RotMat;
	Matrix4x4 m_PosMat;
	Matrix4x4 m_RevolveMat;

	Matrix4x4 m_World;

public:
	Vector2f GetLocal2DPosition()
	{
		Vector2f returnValue = Vector2f(m_LocalPos.x, m_LocalPos.y);
		return returnValue;
	}
	Vector2f GetLocal2DScale()
	{
		Vector2f returnValue = Vector2f(m_LocalScale.x, m_LocalScale.y);
		return returnValue;
	}
	Vector2f GetWorld2DPosition()
	{
		Vector2f returnValue = Vector2f(m_WorldPos.x, m_WorldPos.y);
		return returnValue;
	}
	Vector2f GetWorld2DScale()
	{
		Vector2f returnValue = Vector2f(m_WorldScale.x, m_WorldScale.y);
		return returnValue;
	}
	Vector3f GetLocalScale()const { return m_LocalScale	; }
	Vector3f GetLocalRotate()const { return m_LocalRot	; }
	Vector3f GetLocalPosition()const { return m_LocalPos	; }
	Vector3f GetRevolve()const { return m_Revolve; }

	Vector3f GetWorldScale()const	{ return m_WorldScale;	}
	Vector3f GetWorldRotate()const	{ return m_WorldRot;	}
	Vector3f GetWorldPosition()const{ return m_WorldPos;	}

	void SetLocalScale		(float _x, float _y, float _z)		{ m_LocalScale = Vector3f(_x,_y,_z);	CalWorldScale();	m_UpdateGeo |= TRANSUPDATE_SCALE;	}
	void SetLocalScale		(const Vector3f& ref)				{ m_LocalScale = ref;					CalWorldScale();	m_UpdateGeo |= TRANSUPDATE_SCALE;	}
	void SetLocalRotate		(float _x, float _y, float _z)		{ m_LocalRot = Vector3f(_x, _y, _z);	CalWorldRotate();	m_UpdateGeo |= TRANSUPDATE_ROTATE;	}
	void SetLocalRotate		(const Vector3f& ref)				{ m_LocalRot = ref;						CalWorldRotate();	m_UpdateGeo |= TRANSUPDATE_ROTATE;	}
	void SetLocalPosition	(float _x, float _y, float _z)		{ m_LocalPos = Vector3f(_x, _y, _z);	CalWorldPosition();	m_UpdateGeo |= TRANSUPDATE_POSITION;}
	void SetLocalPosition	(const Vector3f& ref)				{ m_LocalPos = ref;						CalWorldPosition();	m_UpdateGeo |= TRANSUPDATE_POSITION;}
	void SetRevolve			(float _x, float _y, float _z)		{ m_Revolve = Vector3f(_x, _y, _z);		m_UpdateGeo |= TRANSUPDATE_REVOLVE;	}
	void SetRevolve			(const Vector3f& ref)				{ m_Revolve = ref;						m_UpdateGeo |= TRANSUPDATE_REVOLVE;	}

	void SetWorldScale(float _x, float _y, float _z);
	void SetWorldScale(const Vector3f& ref);
	void SetWorldRotate(float _x, float _y, float _z);
	void SetWorldRotate(const Vector3f& ref);
	void SetWorldPosition(float _x, float _y, float _z);
	void SetWorldPosition(const Vector3f& ref);


	Vector3f Foward()const	{ return m_RotMat.vec2; }
	Vector3f Right()const	{ return m_RotMat.vec0; }
	Vector3f Up()const		{ return m_RotMat.vec1; }

	Vector3f WorldFoward()const { return m_World.vec2; }
	Vector3f WorldRight()const	{ return m_World.vec0; }
	Vector3f WorldUp()const		{ return m_World.vec1; }

	const Matrix4x4& GetWorldMartix()const
	{
		return m_World;
	}
	const Matrix4x4 GetParentMatrix()const;
public:
	void Translate(float _x, float _y, float _z)
	{
		//m_LocalPos.x += _x;
		//m_LocalPos.y += _y;
		//m_LocalPos.z += _z;
		SetWorldPosition(m_WorldPos + Vector3f(_x,_y,_z));
		m_UpdateGeo |= TRANSUPDATE_POSITION;
	}
	void Translate(const Vector3f& ref)
	{
		//m_LocalPos += ref;
		SetWorldPosition(m_WorldPos + ref);
		m_UpdateGeo |= TRANSUPDATE_POSITION;

	}
	void Rotate(float _x, float _y, float _z)
	{

		m_LocalRot.x += _x;
		m_LocalRot.y += _y;
		m_LocalRot.z += _z;
		m_UpdateGeo |= TRANSUPDATE_ROTATE;
	}

	void Rotate(const Vector3f& ref)
	{
		m_LocalRot += ref;
		m_UpdateGeo |= TRANSUPDATE_ROTATE;
	}
	void Revolve(float _x, float _y, float _z)
	{
		m_Revolve.x += _x;
		m_Revolve.y += _y;
		m_Revolve.z += _z;
		m_UpdateGeo |= TRANSUPDATE_REVOLVE;
	}
	void Revolve(const Vector3f& ref)
	{
		m_Revolve += ref;
		m_UpdateGeo |= TRANSUPDATE_REVOLVE;
	}
public:
	virtual bool Init() override;
	virtual void EndUpdate() override;
	virtual void FinalUpdate() override;
private:
	void CalWorldScale();
	void CalWorldRotate();
	void CalWorldPosition();

public:
	Transform();
	virtual ~Transform();
};

