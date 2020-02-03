#include "TextureImporter.h"
#include "../External/stb_image.h"
#include "../Platform/Windows/WinExceptions.h"

namespace TEngine
{
	TextureImporter::TextureImporter(uint32 maxInCache)
		: ResourceImporter(maxInCache)
	{
	}

	Texture& TextureImporter::Load(const std::string& path, bool useCache)
	{
		int width, height, nrComponents;
		unsigned char* data = stbi_load(path.c_str(), &width, &height, &nrComponents, 4);
		if (data)
		{
			loadedResources[path] = Texture(width, height, TexFormat::RGBA, TexType::diffuse, data, 0, path);

			return loadedResources[path];

			//stbi_image_free(data);
		}
		else
		{
			stbi_image_free(data);
			throw EXCEPTION("TextureImporter::Load: Could not load dxTexture");
		}
	}
}
