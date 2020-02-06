#pragma once
#include "../../Core/PortableTypes.h"
#include "../../Core/Math/Vector3.h"

namespace TEngine
{
	struct PointLight
	{
		Vector3 color;
		F32 intensity;
		F32 range;
	};
}
