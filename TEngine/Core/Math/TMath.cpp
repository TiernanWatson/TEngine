#define _USE_MATH_DEFINES // Allows use of cmath consts
#include "TMath.h"
#include <cfloat>

namespace TEngine
{
	const float32 TMath::PI = M_PI;
	const float32 TMath::PI_2 = M_PI_2;
	const float32 TMath::PI_4 = M_PI_4;
	const float32 TMath::EPSILON = FLT_EPSILON;
	const float32 TMath::DEG2RAD = TMath::PI / 180.f;
	const float32 TMath::RAD2DEG = 180.f / TMath::PI;
}