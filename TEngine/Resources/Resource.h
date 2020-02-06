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
		Resource(U32 r_id, std::string path);

		U32 GetId() const;
		std::string GetPath() const;

	protected:
		U32 r_id_;
		std::string path_;
	};
}
