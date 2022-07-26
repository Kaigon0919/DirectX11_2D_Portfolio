#include "SystemCore.h"
#include"MainWindow.h"
#include "DxDevice.h"
#include"RenderMgr.h"
#include"PathManager.h"
#include"MySound.h"
bool SystemCore::m_CoreRun = true;


SystemCore::SystemCore()
{
}


SystemCore::~SystemCore()
{
}

void SystemCore::Start(CoreBuilder * _CoreBuilder, HINSTANCE hInstance, const wchar_t * windowName,Vector2i Size /*= { 1280,720 }*/)
{
	MySound::SoundInit();
	PathManager::RootToCreatePath(L"Shader");

	MainWindow::m_hInst = hInstance;
	MainWindow::Init(windowName);
	MainWindow::ReSize(Size);
	DxDevice::Init();

	_CoreBuilder->Build();

	MSG msg;

	while (true == m_CoreRun)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			MainWindow::Progress();
		}
	}
}

void SystemCore::Start(CoreBuilder * _CoreBuilder, HINSTANCE hInstance, const wchar_t * windowName, HWND _OtherWindow )
{
	MySound::SoundInit();

	PathManager::RootToCreatePath(L"Shader");

	MainWindow::m_hInst = hInstance;
	MainWindow::Init(_OtherWindow, windowName);
	DxDevice::Init();

	_CoreBuilder->Build();
}
