#include "ResourceLoader.h"
#include "ResourceImporter.h"

namespace TEngine
{
	ResourceLoader::ResourceLoader()
		: texImporter(100), modelImporter(100)
	{
	}

	Texture& ResourceLoader::GetTexture(const std::string& name, bool useCache)
	{
		return texImporter.Load(name, useCache);
	}

	Model& ResourceLoader::GetModel(const std::string& path, bool useCache)
	{
		return modelImporter.Load(path, useCache);
	}

	ResourceLoader& ResourceLoader::Instance()
	{
		static ResourceLoader instance;
		return instance;
	}
}
