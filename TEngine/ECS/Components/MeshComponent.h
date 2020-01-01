#pragma once
#include "../../Core/PortableTypes.h"
#ifdef OPENGL
#include "../../Render/GLTextureInfo.h"
#endif

namespace TEngine
{
	class Mesh;

	struct MeshComponent
	{
		Mesh* mesh;
		maxint indexCount;
#ifdef OPENGL
		GLTextureInfo* textures;
		uint32 VAO;
		uint32 texCount;
#endif

#ifdef OPENGL
		inline GLTextureInfo& GetTexInfo(uint32 index) 
		{
			return textures[index];
		}
#endif
	};
}
