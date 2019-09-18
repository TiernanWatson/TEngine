#pragma once
#include "../../Core/PortableTypes.h"
#include <string>

namespace TEngine
{
	enum class TexType
	{
		diffuse,
		specular
	};

	class Texture
	{
	public:
		Texture() = default;
		Texture(const std::string& filePath, TexType type = TexType::diffuse);

		void Load();
		void Unload();

		void Use();

	private:
		uint32 id;
		uint32 width, height, nrChannels;

		TexType type;

		std::string path;
	};
}
