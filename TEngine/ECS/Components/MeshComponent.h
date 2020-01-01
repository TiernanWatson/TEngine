#pragma once
#include "../../Core/PortableTypes.h"
#ifdef OPENGL
#include <glad/glad.h>
#include "../../Render/GLTextureInfo.h"
#endif

namespace TEngine
{
	class Mesh;

	struct MeshComponent
	{
		Mesh* mesh;
		GLsizei indexCount;
#ifdef OPENGL
		GLTextureInfo* textures;
		GLuint VAO;
		GLuint texCount;
#endif

#ifdef OPENGL
		_FORCE_INLINE_ GLTextureInfo& GetTexInfo(uint32 index) 
		{
			return textures[index];
		}
#endif
	};
}
