#pragma once
#include "../../Core/PortableTypes.h"
#include "../../Core/Math/Vector3.h"

namespace TEngine
{
	struct PointLight
	{
		Vector3 color;
		float32 intensity;
		float32 range;
	};
}
