#pragma once
#include "../../Core/PortableTypes.h"
#include "../../Core/Math/Vector3.h"

namespace TEngine
{
	struct Transform
	{
		Vector3 localPosition;
		Vector3 localRotation;
		Vector3 localScale;
	};
}
