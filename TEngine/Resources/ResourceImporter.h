#pragma once
#include "../Core/PortableTypes.h"
#include "../Core/Memory/PoolAllocator.h"
#include <vector>
#include <unordered_map>
#include <string>

namespace TEngine
{
	class Resource;

	/**
	* Base class for importing code different types of resources
	* Also contains the cache for faster imports/memory saving
	**/
	template<typename T>
	class ResourceImporter
	{
	public:
		ResourceImporter(uint32 maxInCache);

		virtual T& Load(const std::string& path, bool useCache = true) = 0;

		bool CanImport(const std::string& file);

	protected:
		std::vector<std::string> acceptedExtensions;

		PoolAllocator resourcePool;
		std::unordered_map<std::string, T> loadedResources;
	};

	template<typename T>
	inline ResourceImporter<T>::ResourceImporter(uint32 maxInCache)
		: resourcePool(sizeof(T), maxInCache)
	{
	}

	template<typename T>
	inline bool ResourceImporter<T>::CanImport(const std::string& file)
	{
		std::string ext = file.substr(file.find_last_of('.'), file.npos);

		for (std::string& s : acceptedExtensions)
		{
			if (s == ext) return true;
		}

		return false;
	}
}
