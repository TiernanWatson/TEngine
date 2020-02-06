#pragma once
#include "../../Core/PortableTypes.h"
#include "../../Core/Math/TMath.h"

namespace TEngine
{
	struct Camera
	{
		F32 fov = TMath::kPi_4;
		F32 aspect = 16.f / 9.f;
		F32 far_dist = 100.f;
		F32 near_dist = 0.1f;
	};
}
