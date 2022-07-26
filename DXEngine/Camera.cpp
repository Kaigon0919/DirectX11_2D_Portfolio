#include "Camera.h"
#include"Actor.h"
#include"Level.h"
#include"MainWindow.h"
#include"Transform.h"

void Camera::OnViewGroup(int _groupNumber)
{
	if (_groupNumber < 0 || _groupNumber >= (int)GetLayerNumber())
	{
		return;
	}
	m_RenderLayer |= (1 << _groupNumber);
	GetActor()->GetLevel()->RMgr.CreateRenderOrder(_groupNumber);
}

void Camera::OffViewGroup(int _groupNumber)
{
	if (_groupNumber < 0)
	{
		return;
	}
	int SubBit = m_RenderLayer & (1 << _groupNumber);
	m_RenderLayer ^= SubBit;
}

bool Camera::CheckLayerOn(int _layer)
{
	if (_layer < 0)
	{
		return false;
	}
	return ((m_RenderLayer & (1 << _layer)) != 0);
}

bool Camera::Init(int _Order)
{
	if (nullptr == GetTransform())
	{
		assert(false);
		return false;
	}

	if (nullptr == GetActor()->GetLevel()->GetMainCamera())
	{
		GetActor()->GetLevel()->SetMainCamera(this);
		m_bMain = true;
	}

	m_Order = _Order;

	GetActor()->GetLevel()->RMgr.InsertCamera(this);

	return true;
}

void Camera::EndUpdate()
{
	if (GetTransform() == nullptr)
	{
		assert(false);
		return;
	}

	switch (m_eCameraMode)
	{
	case Camera::CAMERA_MODE_PERSPECTIVE:
		break;
	case Camera::CAMERA_MODE_ORTHOGRAPHIC:
		switch (m_eOrthSizeMode)
		{
		case Camera::ORTH_SIZE_WINDOW:
			m_OrthSize = MainWindow::GetSize();
			break;
		case Camera::ORTH_SIZE_FREE:
			break;
		default:
			assert(false && L"m_eOrthSizeMode value : default");
			break;
		}
		m_View.ViewToLH(GetTransform()->GetWorldPosition(), GetTransform()->Foward(), GetTransform()->Up());
		m_Proj.Orth(m_OrthSize.x / m_Zoom, m_OrthSize.y / m_Zoom, m_CameraNear, m_CameraFar);
		break;
	default:
		assert(false && L"m_eCaera value : default");
		return;
	}
	m_VP = m_View * m_Proj;
}

Vector2f Camera::ScreenToClient(Vector2i screenPos)
{

//	WorldX = SPos.x - SSize.x / 2
//	WorldY = SSize.y / 2 - SPos.y

	Vector3f cameraPos = GetTransform()->GetWorldPosition();
	Vector2i windowSize = MainWindow::GetSize();
	Vector2f worldPos = Vector2f();

	// 창 크기가 아닌 해상도에 따른 변화만 수정하면 완료.
	//worldPos.x = (screenPos.x - windowSize.x / 2.0f) / m_Zoom + cameraPos.x;
	//worldPos.y = (windowSize.y / 2.0f - screenPos.y) / m_Zoom + cameraPos.y;
	


	worldPos.x = (((float)screenPos.x / (float)windowSize.x *m_OrthSize.x) - m_OrthSize.x / 2.0f) / m_Zoom + cameraPos.x;
	worldPos.y = (m_OrthSize.y / 2.0f - ((float)screenPos.y / (float)windowSize.y * m_OrthSize.y)) / m_Zoom + cameraPos.y;
	return worldPos;
}
void Camera::SetOrthSizeMode(ORTH_SIZE_MODE mode, const Vector2i& Size)
{
	m_eOrthSizeMode = mode;
	m_OrthSize = Size;
}

Camera::Camera() : m_CameraNear(0.3f), m_CameraFar(1000.0f), m_eCameraMode(CAMERA_MODE_ORTHOGRAPHIC), m_eOrthSizeMode(ORTH_SIZE_WINDOW), m_bMain(false) , m_Zoom(1.0f)
{
}


Camera::~Camera()
{
	if (m_bMain)
	{
		//GetActor()->GetLevel()->SetMainCamera(nullptr);
	}
}
