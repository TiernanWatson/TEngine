#pragma once
#include "../../Core/PortableTypes.h"
#include "../../Core/Math/Vector3.h"

namespace TEngine
{
	struct Transform
	{
		Vector3 position;
		Vector3 rotation;
		Vector3 scale;
	};
}
