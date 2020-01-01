#pragma once
#include "../Core/PortableTypes.h"
#include "../ECS/Components/Transform.h"
#include "GLBufferInfo.h"
#include "GLTextureInfo.h"
#include <vector>

namespace TEngine
{
	struct GLRenderInfo
	{
		Transform* transform;
		GLBufferInfo* bufferInfo;
		std::vector<GLTextureInfo*> texInfo;
	};
}
