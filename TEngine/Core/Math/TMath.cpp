#define _USE_MATH_DEFINES // Allows use of cmath consts
#include "TMath.h"
#include <cfloat>

namespace TEngine
{
	const F32 TMath::kPi = float(M_PI);
	const F32 TMath::kPi_2 = float(M_PI_2);
	const F32 TMath::kPi_4 = float(M_PI_4);
	const F32 TMath::kEpsilon = FLT_EPSILON;
	const F32 TMath::kDeg2Rad = TMath::kPi / 180.f;
	const F32 TMath::kRad2Deg = 180.f / TMath::kPi;
}
