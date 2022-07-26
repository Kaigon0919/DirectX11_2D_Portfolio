#pragma once
#include"VectorData.h"
#include<Windows.h>


class SystemCore
{
private:
	SystemCore();
	~SystemCore();
public:
	friend class MainWindow;
public:
	class CoreBuilder
	{
	public:
		virtual bool Build() = 0;

	protected:
		CoreBuilder() {}
		~CoreBuilder(){}
	};
private:
	static bool m_CoreRun;
public:
	static void Start(CoreBuilder * _CoreBuilder, HINSTANCE hInstance, const wchar_t * windowName, Vector2i Size = Vector2i(1280,720));
	static void Start(CoreBuilder* _CoreBuilder,  HINSTANCE hInstance, const wchar_t* windowName, HWND _OtherWindow);

	template<typename BuilderType>
	static void Start(HINSTANCE hInstance, const wchar_t * windowName, Vector2i Size = Vector2i(1280, 720))
	{
		BuilderType builder;
		Start(&builder, hInstance, windowName, Size);
	}
	template<typename BuilderType>
	static void Start(HINSTANCE hInstance, const wchar_t * windowName, HWND _OtherWindow)
	{
		BuilderType builder;
		Start(&builder, hInstance, windowName, _OtherWindow);
	}
};

#include<crtdbg.h>
#define CORERUN(BuilderType , WindowName, winSize) \
int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)\
{\
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF); \
	new int; \
	BuilderType builder ; \
	SystemCore::Start(&builder, hInstance,WindowName, winSize);\
	return 0;\
}
