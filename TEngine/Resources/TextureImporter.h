#pragma once
#include "../Core/PortableTypes.h"
#include "ResourceImporter.h"
#include "Types/Texture.h"

namespace TEngine
{
	class TextureImporter : public ResourceImporter<Texture>
	{
	public:
		TextureImporter(uint32 maxInCache);

		Texture& Load(const std::string& path, bool useCache = true);
	};
}
