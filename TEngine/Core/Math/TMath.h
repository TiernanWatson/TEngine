#pragma once
#include "../PortableTypes.h"
#include <cmath>

namespace TEngine
{
	class TMath
	{
	private:
		TMath(); // Don't want an instance ever

	public:
		static const float32 PI;
		static const float32 PI_2;
		static const float32 PI_4;
		static const float32 EPSILON;
		static const float32 DEG2RAD;
		static const float32 RAD2DEG;

		// Trigonometry
		static _FORCE_INLINE_ float32 Sin(float32 value) { return sinf(value); }
		static _FORCE_INLINE_ float32 Cos(float32 value) { return cosf(value); }
		static _FORCE_INLINE_ float32 Tan(float32 value) { return tanf(value); }

		static _FORCE_INLINE_ float32 Asin(float32 value) { return atanf(value); }
		static _FORCE_INLINE_ float32 Acos(float32 value) { return acosf(value); }
		static _FORCE_INLINE_ float32 Atan(float32 value) { return atanf(value); }

		static _FORCE_INLINE_ float32 Atan2(float32 y, float32 x) { return atan2f(y, x); }
	};
}
