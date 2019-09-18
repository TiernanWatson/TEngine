#include "Game.h"

namespace TEngine
{
	void Game::Start()
	{
		Loop::Instance().Run();
	}

	void Game::Exit()
	{
		Loop::Instance().Stop();
	}
}
