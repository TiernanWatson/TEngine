#include "Game.h"
#include "Engine.h"
#include "Core/Config/Config.h"
#include "Core/Config/ConfigVar.h"

namespace TEngine
{
	WindowSettings Game::windowSettings;

#ifdef PLATFORM_WINDOWS
	void Game::Start(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
#else
	void Game::Start()
#endif
	{
		Config::Instance().LoadFrom("D:\\TEngine\\TEngine\\Engine.ini");

		windowSettings.width = CONFIG_INT32("Window", "width", ConfigVar("800"));
		windowSettings.height = CONFIG_INT32("Window", "height", ConfigVar("600"));
		windowSettings.isFullscreen = CONFIG_BOOL("Window", "fullscreen", ConfigVar("true"));
#ifdef PLATFORM_WINDOWS
		windowSettings.hInstance = hInstance;
		windowSettings.pCmdLine = pCmdLine;
		windowSettings.nCmdShow = nCmdShow;
#endif

		//Engine::Instance().Run();
	}

	void Game::Exit()
	{
		//Engine::Instance().Stop();
	}
}
