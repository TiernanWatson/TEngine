#include "WindowsOS.h"
#include "WinExceptions.h"

// Cannot cast member func to this func pointer type, so this is needed
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

namespace TEngine
{
	WindowsOS* WindowsOS::instance = nullptr;

	WindowsOS::WindowsOS(HINSTANCE hInstance, PWSTR pCmdLine, int nCmdShow)
		: hInstance(hInstance), pCmdLine(pCmdLine), nCmdShow(nCmdShow)
	{
		instance = this;
	}

	void WindowsOS::Init()
	{
		InitWindow();
	}

	void WindowsOS::Run()
	{
		isRunning = true;
		mainLoop.StartUp();

		while (isRunning)
		{
			HandleMessages();
			mainLoop.Update();
		}

		mainLoop.ShutDown();

		DestroyWindow(hWnd);
		UnregisterClass(wndClsName, hInstance);
	}

	void WindowsOS::Stop()
	{
		isRunning = false;
	}

	LRESULT WindowsOS::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		switch (uMsg)
		{
		// Window Management
		case WM_CLOSE:
			Stop();
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		case WM_KILLFOCUS:
			keyboard.Clear();
			break;
		// Input Management
		case WM_KEYDOWN:
		case WM_SYSKEYDOWN:
			if (!(lParam & 0x40000000) || keyboard.AutorepeatOn())
				keyboard.OnKeyPress(static_cast<unsigned char>(wParam));
			break;
		case WM_KEYUP:
		case WM_SYSKEYUP:
			keyboard.OnKeyRelease(static_cast<unsigned char>(wParam));
			break;
		case WM_MOUSEMOVE:
			const POINTS pt = MAKEPOINTS(lParam);
			mouse.OnMouseMove(pt.x, pt.y);
			break;
		case WM_LBUTTONDOWN:
			const POINTS pt2 = MAKEPOINTS(lParam);
			mouse.OnLeftDown(pt2.x, pt2.y);
			break;
		case WM_RBUTTONDOWN:
			const POINTS pt3 = MAKEPOINTS(lParam);
			mouse.OnRightDown(pt3.x, pt3.y);
			break;
		case WM_LBUTTONUP:
			const POINTS pt4 = MAKEPOINTS(lParam);
			mouse.OnLeftUp(pt4.x, pt4.y);
			break;
		case WM_RBUTTONUP:
			const POINTS pt5 = MAKEPOINTS(lParam);
			mouse.OnRightUp(pt5.x, pt5.y);
			break;
		}

		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}

	WindowsOS& WindowsOS::GetInstance()
	{
		return *instance;
	}

	void WindowsOS::InitWindow()
	{
		wc = { };
		wc.style = CS_DBLCLKS;
		wc.lpfnWndProc = ::WindowProc;
		wc.hInstance = hInstance;
		wc.lpszClassName = wndClsName;
		wc.lpszMenuName = NULL;
		wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
		wc.hCursor = LoadCursor(NULL, IDC_ARROW);
		wc.cbClsExtra = 0;
		wc.cbWndExtra = 0;

		RegisterClass(&wc);

		hWnd = CreateWindowEx(
			0,
			wndClsName,
			"Odyssey WindowsOS Build",
			WS_OVERLAPPEDWINDOW,

			// Size and position
			CW_USEDEFAULT, CW_USEDEFAULT, 800, 600,

			NULL,       // Parent window    
			NULL,       // Menu
			hInstance,  // Instance handle
			NULL        // Additional application data
		);

		if (!hWnd)
		{
			throw EXCEPTION("Failed to initialize window!");
		}

		ShowWindow(hWnd, nCmdShow);
	}

	void WindowsOS::HandleMessages()
	{
		MSG msg = { };
		while (PeekMessage(&msg, hWnd, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
}

using namespace TEngine;

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return WindowsOS::GetInstance().WindowProc(hwnd, uMsg, wParam, lParam);
}
