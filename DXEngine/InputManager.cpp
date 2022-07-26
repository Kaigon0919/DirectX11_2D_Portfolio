#include "InputManager.h"
#include"MainWindow.h"
#include"DxDevice.h"

std::map<std::wstring, SPTR<InputManager::InputData>>::iterator	InputManager::Start;
std::map<std::wstring, SPTR<InputManager::InputData>>::iterator	InputManager::End;
std::map<std::wstring, SPTR<InputManager::InputData>>			InputManager::m_InputData;

Vector2i InputManager::m_MousePos = {};
float InputManager::m_zDelta = 0.0f;

InputManager::InputManager()
{
}


InputManager::~InputManager()
{
}

bool InputManager::IsUp(const wchar_t * _keyName)
{
	InputData* taget = FindNode(_keyName);
	if (!taget)
	{
		return false;
	}
	return 	taget->isUp;
}

bool InputManager::IsDown(const wchar_t * _keyName)
{
	InputData* taget = FindNode(_keyName);
	if (!taget)
	{
		return false;
	}
	return 	taget->isDown;
}

bool InputManager::IsUnPressed(const wchar_t * _keyName)
{
	InputData* taget = FindNode(_keyName);
	if (!taget)
	{
		return false;
	}
	return 	taget->isUnPressed;
}

bool InputManager::IsPressed(const wchar_t * _keyName)
{
	InputData* taget = FindNode(_keyName);
	if (!taget)
	{
		return false;
	}
	return 	taget->isPressed;
}

float InputManager::GetMouseWHeel()
{
	return m_zDelta;
}

void InputManager::MouseUpdate()
{
	POINT mousePoint;
	// OS의 마우스 위치를 받는다.
	GetCursorPos(&mousePoint);
	// OS의 마우스 위치를 윈도우창의 로컬위치로 변환 시킨다.
	ScreenToClient(MainWindow::GetHWND(), &mousePoint);
	m_MousePos = {mousePoint.x, mousePoint.y};	
}


Vector2i InputManager::GetMousePos() 
{
	return m_MousePos;
}
void InputManager::SetMouseWHeel(float _zdelta)
{
	m_zDelta = _zdelta;
}
void InputManager::Update()
{

	MouseUpdate();

	Start = m_InputData.begin();
	End = m_InputData.end();


	for (; Start != End; ++Start)
	{
		if (Start->second != nullptr)
		{
			Start->second->Update();
		}
	}
}

void InputManager::Clear()
{
	m_zDelta = 0.0f;
}



///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// InputData Function.
// 
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

void InputManager::InputData::Update()
{
	bool keyCheck = AllKeyCheck();

	if (keyCheck)
	{
		if (isUnPressed)
		{
			isUp = false;
			isUnPressed = false;
			isDown = true;
			isPressed = true;
		}
		else
		{
			isUp = false;
			isUnPressed = false;
			isDown = false;
			isPressed = true;
		}
	}
	else if (keyCheck == false)
	{
		if (isPressed)
		{
			isUp = true;
			isUnPressed = true;
			isDown = false;
			isPressed = false;
		}
		else
		{
			isUp = false;
			isUnPressed = true;
			isDown = false;
			isPressed = false;
		}
	}
}

bool InputManager::InputData::AllKeyCheck()
{
	if (!MainWindow::IsFocus())
	{
		return false;
	}
	for (size_t i = 0; i < m_key.size(); ++i)
	{
		if (GetAsyncKeyState(m_key[i]) == 0)
		{
			return false;
		}
	}
	return true;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////