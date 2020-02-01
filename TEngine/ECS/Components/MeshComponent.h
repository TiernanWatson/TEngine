#pragma once
#include "../../Core/PortableTypes.h"
#ifdef DIRECTX
#include <d3d11.h>
#include <wrl.h>
#endif
#ifdef OPENGL
#include <glad/glad.h>
#include "../../Render/OpenGL/GLTextureInfo.h"
#endif

namespace wrl = Microsoft::WRL;

namespace TEngine
{
	class Mesh;

	struct MeshComponent
	{
		Mesh* mesh;
#ifdef DIRECTX
		wrl::ComPtr<ID3D11Buffer> vertexBuffer;
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
