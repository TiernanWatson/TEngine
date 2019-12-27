#pragma once
#include "../../Core/PortableTypes.h"

namespace TEngine
{
	struct Texture;

	/**
	* Class consisting of static members for 
	* the management of the game's textures
	**/
	class Textures
	{
	public:
		Textures() = delete;

		static uint32 LoadTextureGL(Texture& tex);
	};
}
