#pragma once
#include "../../Core/PortableTypes.h"
#include <string>

namespace TEngine
{
	enum class TexType
	{
		diffuse,
		specular,
		normal,
		height
	};

	struct Texture
	{
		uint32 id;
		TexType type;
		std::string path;
	};
}
