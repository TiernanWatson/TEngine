#pragma once
#include "../PortableTypes.h"
#include <cmath>

namespace TEngine
{
	/**
	* Collection of common math functions
	**/
	namespace TMath
	{
		extern const F32 kPi;
		extern const F32 kPi_2;
		extern const F32 kPi_4;
		extern const F32 kEpsilon;
		extern const F32 kDeg2Rad;
		extern const F32 kRad2Deg;

		_FORCE_INLINE_ F32 Sin(F32 value) { return sinf(value); }
		_FORCE_INLINE_ F32 Cos(F32 value) { return cosf(value); }
		_FORCE_INLINE_ F32 Tan(F32 value) { return tanf(value); }

		_FORCE_INLINE_ F32 Asin(F32 value) { return asinf(value); }
		_FORCE_INLINE_ F32 Acos(F32 value) { return acosf(value); }
		_FORCE_INLINE_ F32 Atan(F32 value) { return atanf(value); }

		_FORCE_INLINE_ F32 Atan2(F32 y, F32 x) { return atan2f(y, x); }

		_FORCE_INLINE_ USIZE Min(USIZE val1, USIZE val2)
		{
			return (val1 < val2) ? val1 : val2;
		}
	};
}
