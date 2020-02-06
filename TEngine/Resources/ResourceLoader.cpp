#include "ResourceLoader.h"
#include "ResourceImporter.h"

namespace TEngine
{
	ResourceLoader::ResourceLoader()
		: tex_importer_(100), model_importer_(100)
	{
	}

	Texture& ResourceLoader::GetTexture(const std::string& name, bool useCache)
	{
		return tex_importer_.Load(name, useCache);
	}

	Model& ResourceLoader::GetModel(const std::string& path, bool useCache)
	{
		return model_importer_.Load(path, useCache);
	}

	ResourceLoader& ResourceLoader::Instance()
	{
		static ResourceLoader instance;
		return instance;
	}
}
