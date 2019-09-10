#include "Loop.h"

namespace TEngine
{
	Loop::Loop() 
	{
		windowManager = new WindowManager();
	}

	Loop::~Loop()
	{
		delete windowManager;
	}

	Loop& Loop::Instance()
	{
		static Loop instance;
		return instance;
	}

	void Loop::Run()
	{
		StartUp();
		while (isRunning)
		{
			Update();
		}
		ShutDown();
	}

	void Loop::StartUp()
	{
		windowManager->StartUp();
	}

	void Loop::Update()
	{
		windowManager->Update(1.f);
	}

	void Loop::ShutDown()
	{
		windowManager->ShutDown();
	}
}
