#pragma once
#include "../../Core/Math/Vector3.h"
#include "../../Core/Math/Vector2.h"

namespace TEngine
{
	struct Vertex
	{
		Vector3 position;
		Vector3 normal;
		Vector3 tangent;
		Vector3 bitangent;
		Vector2 textCoord;
	};
}
