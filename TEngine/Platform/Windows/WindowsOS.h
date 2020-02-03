#pragma once
#include "WinHeader.h"
#include "../../Engine.h"
#include "Keyboard.h"
#include "Mouse.h"

namespace TEngine
{
	/**
	* Represents an instance of this program on WindowsOS,
	* there should only ever be one instance WindowsOS::Get
	**/
	class WindowsOS
	{
	public:
		WindowsOS(HINSTANCE hInstance, PWSTR pCmdLine, int nCmdShow);

		void Init();
		void Run();
		void Stop();

		LRESULT WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

		inline HINSTANCE GetHINSTANCE() const
		{
			return hInstance;
		}

		inline HWND GetHWND() const
		{
			return hWnd;
		}

		inline int GetWidth() const
		{
			return width;
		}

		inline int GetHeight() const
		{
			return height;
		}

		static WindowsOS& Get();

	private:
		void InitWindow();
		void HandleMessages();

		// Windows API Stuff
		HINSTANCE hInstance;
		PWSTR pCmdLine;
		int nCmdShow;

		WNDCLASS wc;
		HWND hWnd;

		const char* wndClsName = "OddWinCls";

		int width = 800;
		int height = 600;
		bool fullscreen = false;

		// Game Engine Stuff
		bool isRunning = false;

		Engine mainLoop;
		Keyboard keyboard;
		Mouse mouse;

		static WindowsOS* instance;
	};
}
