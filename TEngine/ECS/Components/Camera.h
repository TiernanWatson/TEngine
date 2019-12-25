#pragma once
#include "../../Core/PortableTypes.h"
#include "../../Core/Math/TMath.h"

namespace TEngine
{
	struct Camera
	{
		float32 FOV = TMath::PI_4;
		float32 aspect = 16.f / 9.f;
		float32 farDist = 100.f;
		float32 nearDist = 0.1f;
	};
}
