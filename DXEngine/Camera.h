#pragma once
#include "Component.h"
#include"VectorData.h"
class Camera :	public Component
{
public:
	friend class Actor;
public:
	enum CAMERA_MODE
	{
		CAMERA_MODE_PERSPECTIVE,
		CAMERA_MODE_ORTHOGRAPHIC
	};
	enum ORTH_SIZE_MODE
	{
		ORTH_SIZE_WINDOW,
		ORTH_SIZE_FREE,
	};
private:
	bool m_bMain;
	CAMERA_MODE m_eCameraMode;
	ORTH_SIZE_MODE m_eOrthSizeMode;
	Vector2f m_OrthSize;

	float m_CameraNear;
	float m_CameraFar;
	float m_Zoom;
	Matrix4x4 m_View;
	Matrix4x4 m_Proj;
	Matrix4x4 m_VP;

	int m_Order;
public:
	int GetOrder()const
	{
		return m_Order;
	}
	Matrix4x4 GetMatrixVP()const
	{
		return m_VP;
	}
	void SetZoom(float _zoom)
	{
		m_Zoom = _zoom;
	}
	void AddZoom(float _zoom)
	{
		m_Zoom += _zoom;
	}
private:
	int m_RenderLayer;
public:
	void OnViewGroup(int _groupNumber);
	void OffViewGroup(int _groupNumber);

	template<typename ...Rest>
	void OnViewGroup(Rest ..._Arg)
	{
		OnGroup(_Arg...);
	}
	template<typename ...Rest>
	void OffViewGroup(Rest ..._Arg)
	{
		OffGroup(_Arg...);
	}

	static size_t GetLayerNumber()
	{
		return (sizeof(m_RenderLayer) * 8); // Layer 자료형에 따라 사이즈가 달라지고, 비트 갯수를 넘기기 위해 '8'를 곱한다.
	}
	bool CheckLayerOn(int _layer);

private:
	template<typename ...Rest>
	void OnGroup(int _groupNumber, Rest ..._Arg)
	{
		OnViewGroup(_groupNumber);
		OnGroup(_Arg...);
	}
	void OnGroup(int _groupNumber)
	{
		OnViewGroup(_groupNumber);
	}

	template<typename ...Rest>
	void OffGroup(int _groupNumber, Rest ..._Arg)
	{
		OffViewGroup(_groupNumber);
		OffGroup(_Arg...);
	}
	void OffGroup(int _groupNumber)
	{
		OffViewGroup(_groupNumber);
	}

private:
	bool Init(int _Order = 0);
	void EndUpdate() override;
public:
	Vector2f ScreenToClient(Vector2i screenPos);
	void SetOrthSizeMode(ORTH_SIZE_MODE mode, const Vector2i& Size);
	Vector2i GetOrthSize()const
	{
		return m_OrthSize;
	}
public:
	Camera();
	~Camera();
};

