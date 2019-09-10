#pragma once
#include "../PortableTypes.h"
#include <chrono>

namespace TEngine
{
	class Clock
	{
	private:
		typedef std::chrono::nanoseconds				Nanoseconds;
		typedef std::chrono::high_resolution_clock		HighResClock;
		typedef std::chrono::time_point<HighResClock>	TimePoint;

		bool isPaused;

		TimePoint startTime;
		TimePoint currentTime;
		float64 elapsedTime;
		float64 deltaTime;

	public:
		Clock();

		void Update();

		float64 GetDeltaTime();
		float64 GetElapsedTime();

		void SetPause(bool value);
		bool IsPaused();
	};
}
