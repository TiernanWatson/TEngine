#pragma once
#include "../Core/PortableTypes.h"
#include "ResourceImporter.h"
#include "Types/Texture.h"

namespace TEngine
{
	class TextureImporter : public ResourceImporter<Texture>
	{
	public:
		TextureImporter(U32 max_in_cache);

		Texture& Load(const std::string& path, bool use_cache = true);
	};
}
