#pragma once
#include "../Core/PortableTypes.h"
#include <string>

namespace TEngine
{
	/*
	* Base for loadable resources (e.g. Textures, Materials, Meshes)
	*/
	class Resource
	{
	public:
		Resource();
		Resource(uint32 rId, std::string path);

		uint32 GetId() const;
		std::string GetPath() const;

	protected:
		uint32 rId;
		std::string path;
	};
}
