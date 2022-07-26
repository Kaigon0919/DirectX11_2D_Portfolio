#include "MainWindow.h"
#include"SystemCore.h"
#include"DxDevice.h"
#include"RenderMgr.h"
#include"Level.h"
#include"RenderMgr.h"
#include"TimeManager.h"
#include"InputManager.h"

HINSTANCE MainWindow::m_hInst;
HWND MainWindow::m_hWnd;
HDC MainWindow::m_hDC;
Vector2i MainWindow::m_Size;
bool MainWindow::m_isFull = false;


MainWindow::MainWindow()
{
}


MainWindow::~MainWindow()
{
}

void MainWindow::Register()
{
	WNDCLASSEXW wcex;
	wcex.cbSize = sizeof(WNDCLASSEXW);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = m_hInst;
	wcex.hIcon = nullptr;
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = nullptr;
	wcex.lpszClassName = L"Kaigon";
	wcex.hIconSm = nullptr;

	RegisterClassExW(&wcex);
}

bool MainWindow::CreateWindows(const wchar_t * windowName)
{
	m_hWnd = CreateWindowW(L"Kaigon", windowName, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, m_hInst, nullptr);

	if (!m_hWnd)
	{
		return false;
	}

	ShowWindow(m_hWnd, SW_SHOW);
	UpdateWindow(m_hWnd);

	return true;
}

void MainWindow::Init(const wchar_t * name)
{
	Register();
	CreateWindows(name);
	m_hDC = GetDC(m_hWnd);
}

void MainWindow::Init(HWND hWnd, const wchar_t * name)
{

	m_hWnd = hWnd;

	RECT rt;
	GetClientRect(hWnd, &rt);
	m_Size.x = rt.right;
	m_Size.y = rt.bottom;
	SetWindowText(hWnd, name);
	m_hDC = GetDC(m_hWnd);
}

LRESULT MainWindow::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
		SystemCore::m_CoreRun = false;
		break;
	case WM_MOUSEWHEEL:
	{
		InputManager::SetMouseWHeel(float(GET_WHEEL_DELTA_WPARAM(wParam) / WHEEL_DELTA));
	}
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

void MainWindow::Progress()
{
	TimeManager::Update();
	InputManager::Update();
	Level::LevelUpdate();
	InputManager::Clear();
}

void MainWindow::ReSize(int Width, int Height)
{
	m_Size = Vector2i(Width, Height);
	RECT rect = { 0,0, Width, Height };
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);
	SetWindowPos(m_hWnd, nullptr, 0, 0, rect.right - rect.left, rect.bottom - rect.top, SWP_NOZORDER | SWP_NOMOVE);
}

void MainWindow::ReSize(Vector2i size)
{
	m_Size = size;
	RECT rect = { 0,0, size.x, size.y};
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);
	SetWindowPos(m_hWnd, nullptr, 0, 0, rect.right - rect.left, rect.bottom - rect.top, SWP_NOZORDER | SWP_NOMOVE);
}
