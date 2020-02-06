#pragma once
#include "../PortableTypes.h"
#include <chrono>

namespace TEngine
{
	class Clock
	{
	public:
		Clock();

		void Update();

		F64 GetDeltaTime();
		F64 GetElapsedTime();

		void SetPause(bool value);
		bool IsPaused();

	private:
		typedef std::chrono::nanoseconds				Nanoseconds;
		typedef std::chrono::high_resolution_clock		HighResClock;
		typedef std::chrono::time_point<HighResClock>	TimePoint;

		bool is_paused_;

		TimePoint start_time_;
		TimePoint current_time_;
		F64 elapsed_time_;
		F64 delta_time_;
	};
}
