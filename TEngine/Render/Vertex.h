#pragma once
#include "../Core/PortableTypes.h"
#include "../Core/Math/Vector3.h"
#include "../Core/Math/Vector2.h"

namespace TEngine
{
	struct Vertex
	{
		Vector3 position;
		Vector3 normal;
		Vector2 tex_coord;
	};

	struct Vertex2D
	{
		Vector2 position;
		Vector2 tex_coord;
	};
}
