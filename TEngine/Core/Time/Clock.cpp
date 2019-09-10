#include "Clock.h"

namespace TEngine
{
	Clock::Clock() : isPaused(false),
		startTime(HighResClock::now()),
		currentTime(HighResClock::now()),
		elapsedTime(0.f),
		deltaTime(0.f)
	{
	}

	void Clock::SetPause(bool value)
	{
		isPaused = value;
	}

	bool Clock::IsPaused()
	{
		return isPaused;
	}

	void Clock::Update()
	{
		if (isPaused) return;

		TimePoint now = HighResClock::now();

		Nanoseconds delta = now - currentTime;
		Nanoseconds elapsed = now - startTime;

		currentTime = now;
		deltaTime = delta.count() * 1e-9;
		elapsedTime = elapsed.count() * 1e-9;
	}

	float64 Clock::GetDeltaTime()
	{
		return deltaTime;
	}

	float64 Clock::GetElapsedTime()
	{
		return elapsedTime;
	}
}
