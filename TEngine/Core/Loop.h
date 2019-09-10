#pragma once
#include "PortableTypes.h"
#include "Time/Clock.h"
#include "../Window/WindowManager.h"

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

		Loop(); // singleton
		~Loop();

	public:
		static Loop& Instance();

		Clock& GetClock();

		void Run();

	private:
		void StartUp();
		void Update();
		void ShutDown();

		void FixedUpdate(const float32 timeStep);
		void VariableUpdate(const float32 deltaTime);
	};
}
