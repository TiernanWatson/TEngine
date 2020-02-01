#pragma once
#ifdef PLATFORM_WINDOWS
#include <Windows.h>
#endif
#include "Core/PortableTypes.h"
#include "Engine.h"

namespace TEngine
{
	struct WindowSettings
	{
		uint16 width;
		uint16 height;
		bool isFullscreen;
#ifdef PLATFORM_WINDOWS
		HINSTANCE hInstance;
		PWSTR pCmdLine;
		int nCmdShow;
#endif
	};

	class Game
	{
	public:
#ifdef PLATFORM_WINDOWS
		static void Start(
			HINSTANCE hInstance, 
			HINSTANCE hPrevInstance, 
			PWSTR pCmdLine, 
			int nCmdShow);
#else
		static void Start();
#endif
		static void Exit();

		static inline WindowSettings& GetWindowSettings()
		{
			return windowSettings;
		}

		static inline Engine& GetLoop()
		{
			return mainLoop;
		}

	private:
		static WindowSettings windowSettings;

		static Engine mainLoop;
	};
}
