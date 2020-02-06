#include "TextureImporter.h"
#include "../External/stb_image.h"
#include "../Platform/Windows/WinExceptions.h"

namespace TEngine
{
	TextureImporter::TextureImporter(U32 maxInCache)
		: ResourceImporter(maxInCache)
	{
	}

	Texture& TextureImporter::Load(const std::string& path, bool useCache)
	{
		int width, height, nrComponents;
		unsigned char* data = stbi_load(path.c_str(), &width, &height, &nrComponents, 4);
		if (data)
		{
			loaded_resources_[path] = Texture(width, height, TexFormat::RGBA, TexType::diffuse, data, 0, path);

			return loaded_resources_[path];

			//stbi_image_free(data_);
		}
		else
		{
			stbi_image_free(data);
			throw EXCEPTION("TextureImporter::Load: Could not load dx_texture_");
		}
	}
}
