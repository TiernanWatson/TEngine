#pragma once
#include "../Core/PortableTypes.h"
#include "../Resources/Types/Texture.h"
#include <glad/glad.h>

namespace TEngine
{
	struct GLTextureInfo
	{
		GLuint id;
		TexType type;
	};
}
