#pragma once
#include "../../Core/PortableTypes.h"
#ifdef OPENGL
#include <glad/glad.h>
#include "../../Render/OpenGL/GLTextureInfo.h"
#endif

namespace TEngine
{
	class Mesh;
#ifdef DIRECTX
	class DXMeshInstance;
#endif

	struct MeshComponent
	{
		Mesh* mesh;
#ifdef DIRECTX
		DXMeshInstance* mesh_instance;
#endif
#ifdef OPENGL
		GLsizei indexCount;
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
