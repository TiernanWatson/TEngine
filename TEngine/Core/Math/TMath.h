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
		extern const float32 PI;
		extern const float32 PI_2;
		extern const float32 PI_4;
		extern const float32 EPSILON;
		extern const float32 DEG2RAD;
		extern const float32 RAD2DEG;

		// Trigonometry
		_FORCE_INLINE_ float32 Sin(float32 value) { return sinf(value); }
		_FORCE_INLINE_ float32 Cos(float32 value) { return cosf(value); }
		_FORCE_INLINE_ float32 Tan(float32 value) { return tanf(value); }

		_FORCE_INLINE_ float32 Asin(float32 value) { return asinf(value); }
		_FORCE_INLINE_ float32 Acos(float32 value) { return acosf(value); }
		_FORCE_INLINE_ float32 Atan(float32 value) { return atanf(value); }

		_FORCE_INLINE_ float32 Atan2(float32 y, float32 x) { return atan2f(y, x); }
	};
}
