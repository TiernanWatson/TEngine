#include "Clock.h"

namespace TEngine
{
	Clock::Clock() : is_paused_(false),
		start_time_(HighResClock::now()),
		current_time_(HighResClock::now()),
		elapsed_time_(0.f),
		delta_time_(0.f)
	{
	}

	void Clock::SetPause(bool value)
	{
		is_paused_ = value;
	}

	bool Clock::IsPaused()
	{
		return is_paused_;
	}

	void Clock::Update()
	{
		if (is_paused_) return;

		TimePoint now = HighResClock::now();

		Nanoseconds delta = now - current_time_;
		Nanoseconds elapsed = now - start_time_;

		current_time_ = now;
		delta_time_ = delta.count() * 1e-9;
		elapsed_time_ = elapsed.count() * 1e-9;
	}

	F64 Clock::GetDeltaTime()
	{
		return delta_time_;
	}

	F64 Clock::GetElapsedTime()
	{
		return elapsed_time_;
	}
}
