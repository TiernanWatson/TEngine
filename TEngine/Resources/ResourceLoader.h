#pragma once
#include "../Core/PortableTypes.h"
#include "../Core/Memory/PoolAllocator.h"
#include "TextureImporter.h"
#include "ModelImporter.h"
#include <unordered_map>
#include <string>

namespace TEngine
{
	class Resource;
	class Texture;
	class Model;

	/**
	* Main singleton class used to handle the loading of resources
	**/
	class ResourceLoader
	{
	public:
		Texture& GetTexture(const std::string& name, bool use_cache = true);
		Model& GetModel(const std::string& path, bool use_cache = true);

		static ResourceLoader& Instance();

	private:
		ResourceLoader();

		TextureImporter tex_importer_;
		ModelImporter model_importer_;
	};
}
