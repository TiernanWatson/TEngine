#include "TextureImporter.h"
#include "../External/stb_image.h"

namespace TEngine
{
	TextureImporter::TextureImporter(uint32 maxInCache)
		: ResourceImporter(maxInCache)
	{
	}

	Texture& TextureImporter::Load(const std::string& path, bool useCache)
	{
		int width, height, nrComponents;
		unsigned char* data = stbi_load(path.c_str(), &width, &height, &nrComponents, 0);
		if (data)
		{
			CONSOLE_PRINT("STB Loaded image: " + path);

			TexFormat format;
			if (nrComponents == 1)
				format = TexFormat::R;
			else if (nrComponents == 3)
				format = TexFormat::RGB;
			else if (nrComponents == 4)
				format = TexFormat::RGBA;

			loadedResources[path] = Texture(width, height, format, TexType::diffuse, data, 0, path);

			return loadedResources[path];

			//stbi_image_free(data);
		}
		else
		{
			CONSOLE_PRINT("STB FAILED to load image: " + path);

			throw std::exception("TextureImporter::Load: Could not load texture");

			stbi_image_free(data);
		}
	}
}