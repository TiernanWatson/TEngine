#pragma once
#include "Core/PortableTypes.h"
#include "Core/Time/Clock.h"
#include "Window/WindowManager.h"
#include "Input/InputSystem.h"
#include "Render/GLRenderer.h"
#include "World/WorldSystem.h"
#include "Core/Memory/StackAllocator.h"

namespace TEngine
{
	class DebugSystem;

	class Loop
	{
	private:
		bool isRunning = true;
		uint8 maxFixedSteps = 8;		// Maximum number of fixed steps in one iteration
		float32 fixedTimeStep = 0.02f;  // Period of time step
		float64 accumulatedTime = 0.f;  // Time accumulated since last update

		Clock gameClock;

		StackAllocator systemsStack;

		WindowManager* windowManager;
		InputSystem* inputSystem;
		GLRenderer* renderSystem;
		WorldSystem* worldSystem;
#if _DEBUG
		DebugSystem* debugSystem;
#endif

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
