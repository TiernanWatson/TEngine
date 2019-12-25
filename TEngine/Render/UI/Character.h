#pragma once
#include "../../Core/PortableTypes.h"
#include "../../Core/Math/Vector2Int.h"

namespace TEngine
{
	struct Character
	{
		uint32 textureID;
		uint32 advance;
		Vector2Int bearing;
		Vector2Int size;
	};
}
