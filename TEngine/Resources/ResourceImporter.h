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
		ResourceImporter(U32 max_in_cache);

		virtual T& Load(const std::string& path, bool use_cache = true) = 0;

		bool CanImport(const std::string& file);

	protected:
		std::vector<std::string> accepted_extensions_;

		PoolAllocator resource_pool_;
		std::unordered_map<std::string, T> loaded_resources_;
	};

	template<typename T>
	inline ResourceImporter<T>::ResourceImporter(U32 max_in_cache)
		: resource_pool_(sizeof(T), max_in_cache)
	{
	}

	template<typename T>
	inline bool ResourceImporter<T>::CanImport(const std::string& file)
	{
		std::string ext = file.substr(file.find_last_of('.'), file.npos);

		for (std::string& s : accepted_extensions_)
		{
			if (s == ext) return true;
		}

		return false;
	}
}
