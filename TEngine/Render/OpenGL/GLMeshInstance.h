#ifdef OPENGL
#pragma once
#include "../../Core/PortableTypes.h"
#include "GLTextureInfo.h"
#include <glad/glad.h>
#include <vector>

namespace TEngine
{
	class Mesh;
	class Texture;

	/**
	* Represents an instance_ of a mesh on the GPU
	* Useful for saving memory (only kOne copy needed)
	**/
	class GLMeshInstance
	{
	public:
		GLMeshInstance() = default;
		GLMeshInstance(const Mesh* mesh);

		void Load();
		void Unload();

		const Mesh* GetMesh() const;

		GLuint GetVAO() const;
		GLuint GetVBO() const;
		GLuint GetEBO() const;
		const GLTextureInfo* GetTextures() const;
		GLsizei GetTextureCount() const;

	private:
		const Mesh* mesh;

		GLuint VAO, VBO, EBO;

		std::vector<GLTextureInfo> textures;

		bool isLoaded = false;

		void SetupTexture(const Texture* tex);
	};
}
#endif // OPENGL