#pragma once
#include<Windows.h>
#include"VectorData.h"

class MainWindow
{
private:
	MainWindow();
	MainWindow(HWND hWnd);
	~MainWindow();
public:
	friend class SystemCore;
private:
	static HINSTANCE m_hInst;
	static HWND m_hWnd;
	static HDC m_hDC;
	static Vector2i m_Size;
	static bool m_isFull;
private:
	static void Register();
	static bool CreateWindows(const wchar_t * windowName);

	static void Init(const wchar_t * name);
	static void Init(HWND hWnd,const wchar_t * name);

	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
public:
	static void Progress();

public:
	static void ReSize(int xSize, int ySize);
	static void ReSize(Vector2i size);
	static Vector2i GetSize() { return m_Size; }
	static HWND GetHWND() { return m_hWnd; }
	static bool IsFull() { return m_isFull; }
	static bool IsFocus() { return m_hWnd == GetFocus(); }
};

