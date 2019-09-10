#pragma once
#include "PortableTypes.h"
#include "../Window/WindowManager.h"

namespace TEngine
{
	class Loop
	{
	private:
		bool isRunning = true;

		WindowManager* windowManager;

		Loop(); // singleton
		~Loop();

	public:
		static Loop& Instance();

		void Run();

	private:
		void StartUp();
		void Update();
		void ShutDown();
	};
}
