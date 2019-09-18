#pragma once
#include "Core/PortableTypes.h"
#include "Core/Time/Clock.h"
#include "Window/WindowManager.h"
#include "Render/RenderManager.h"

namespace TEngine
{
	class Loop
	{
	private:
		bool isRunning = true;
		uint8 maxFixedSteps = 8;
		float32 fixedTimeStep = 0.02f;
		float64 accumulatedTime = 0.f;

		Clock gameClock;

		WindowManager* windowManager;
		RenderManager* renderManager;

		Loop(); // singleton
		~Loop();

	public:
		static Loop& Instance();

		Clock& GetClock();

		/**
		* Starts the main game loop (usually called from Game::)
		**/
		void Run();

		/**
		* After the in-progress update finishes, the loop will stop and shut down
		**/
		void Stop();

	private:
		void StartUp();
		void Update();
		void ShutDown();

		void FixedUpdate(const float32 timeStep);
		void VariableUpdate(const float32 deltaTime);
	};
}
