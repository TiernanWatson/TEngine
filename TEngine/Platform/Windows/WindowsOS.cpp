#include "WindowsOS.h"
#include "WinExceptions.h"
#include "../../Core/Config/Config.h"
#include "../../Core/Config/ConfigVar.h"

// Cannot cast member func to this func pointer type_, so this is needed
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

namespace TEngine
{
	WindowsOS* WindowsOS::instance = nullptr;

	WindowsOS::WindowsOS(HINSTANCE hInstance, PWSTR pCmdLine, int nCmdShow)
		: hInstance_(hInstance), pCmdLine_(pCmdLine), nCmdShow_(nCmdShow)
	{
		instance = this;

		Config::Instance().LoadFrom("D:\\TEngine\\TEngine\\Engine.ini");

		width_ = CONFIG_INT32("Window", "width_", ConfigVar("800"));
		height_ = CONFIG_INT32("Window", "height_", ConfigVar("600"));
		is_fullscreen_ = CONFIG_BOOL("Window", "is_fullscreen_", ConfigVar("false"));
	}

	void WindowsOS::Init()
	{
		InitWindow();
	}

	void WindowsOS::Run()
	{
		is_running_ = true;
		main_loop_.StartUp();

		while (is_running_)
		{
			HandleMessages();
			main_loop_.Update();
		}

		main_loop_.ShutDown();

		DestroyWindow(hWnd_);
		UnregisterClass(wnd_cls_name_, hInstance_);
	}

	void WindowsOS::Stop()
	{
		is_running_ = false;
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
			//keyboard_.Clear();
			break;
		// Input Management
		case WM_KEYDOWN:
		case WM_SYSKEYDOWN:
			// 0x4.... specifies that key was pressed last frame
			if (!(lParam & 0x40000000) || keyboard_.AutorepeatOn())
				keyboard_.OnKeyPress(static_cast<unsigned char>(wParam));
			break;
		case WM_KEYUP:
		case WM_SYSKEYUP:
			keyboard_.OnKeyRelease(static_cast<unsigned char>(wParam));
			break;
		case WM_MOUSEMOVE:
			const POINTS pt = MAKEPOINTS(lParam);
			mouse_.OnMouseMove(pt.x, pt.y);
			break;
		case WM_LBUTTONDOWN:
			const POINTS pt2 = MAKEPOINTS(lParam);
			mouse_.OnLeftDown(pt2.x, pt2.y);
			break;
		case WM_RBUTTONDOWN:
			const POINTS pt3 = MAKEPOINTS(lParam);
			mouse_.OnRightDown(pt3.x, pt3.y);
			break;
		case WM_LBUTTONUP:
			const POINTS pt4 = MAKEPOINTS(lParam);
			mouse_.OnLeftUp(pt4.x, pt4.y);
			break;
		case WM_RBUTTONUP:
			const POINTS pt5 = MAKEPOINTS(lParam);
			mouse_.OnRightUp(pt5.x, pt5.y);
			break;
		}

		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}

	WindowsOS& WindowsOS::Get()
	{
		return *instance;
	}

	void WindowsOS::InitWindow()
	{
		// Make sure client size_ is desired resolution
		RECT wr;
		wr.left = 100;
		wr.right = width_ + wr.left;
		wr.top = 100;
		wr.bottom = height_ + wr.top;

		if (!AdjustWindowRect(&wr, WS_OVERLAPPEDWINDOW, FALSE))
		{
			throw EXCEPTION("Could not AdjustWindowRect in InitWindow!");
		}

		// Create the window
		wc_ = { };
		wc_.style = CS_DBLCLKS;
		wc_.lpfnWndProc = ::WindowProc;
		wc_.hInstance = hInstance_;
		wc_.lpszClassName = wnd_cls_name_;
		wc_.lpszMenuName = NULL;
		wc_.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
		wc_.hCursor = LoadCursor(NULL, IDC_ARROW);
		wc_.cbClsExtra = 0;
		wc_.cbWndExtra = 0;

		RegisterClass(&wc_);

		hWnd_ = CreateWindowEx(
			0,
			wnd_cls_name_,
			CONFIG_STRING("Window", "title", ConfigVar("Odyssey Engine")).c_str(),
			is_fullscreen_ ? WS_POPUP : WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT, CW_USEDEFAULT,  // Position
			wr.right - wr.left, wr.bottom - wr.top,  // Size
			NULL,  // Parent window    
			NULL,  // Menu
			hInstance_,  
			NULL  // Additional application data_
		);

		if (!hWnd_)
		{
			throw EXCEPTION("Failed to initialize window!");
		}

		ShowWindow(hWnd_, nCmdShow_);
	}

	void WindowsOS::HandleMessages()
	{
		MSG msg = { };
		while (PeekMessage(&msg, hWnd_, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
}

using namespace TEngine;

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return WindowsOS::Get().WindowProc(hwnd, uMsg, wParam, lParam);
}
