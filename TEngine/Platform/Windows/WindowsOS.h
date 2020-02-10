#pragma once
#include "WinHeader.h"
#include "../../Engine.h"
#include "Keyboard.h"
#include "Mouse.h"

namespace TEngine
{
	/**
	* Represents an instance_ of this program on WindowsOS,
	* there should only ever be kOne instance_ WindowsOS::Get
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
			return hInstance_;
		}

		inline HWND GetHWND() const
		{
			return hwnd;
		}

		inline int GetWidth() const
		{
			return width_;
		}

		inline int GetHeight() const
		{
			return height_;
		}

		static WindowsOS& Get();

	private:
		void InitWindow();
		void HandleMessages();

		// Windows API Stuff
		HINSTANCE hInstance_;
		PWSTR pCmdLine_;
		int nCmdShow_;

		WNDCLASS wc_;
		HWND hwnd;

		const char* wnd_cls_name_ = "OddWinCls";

		int width_ = 800;
		int height_ = 600;
		bool is_fullscreen_ = false;

		bool is_running_ = false;

		Engine main_loop_;
		Keyboard keyboard_;
		Mouse mouse_;

		static WindowsOS* instance;
	};
}
