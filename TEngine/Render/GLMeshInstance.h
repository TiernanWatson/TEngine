#pragma once
#include "../Core/PortableTypes.h"
#include "GLTextureInfo.h"
#include <vector>

namespace TEngine
{
	class Mesh;
	class Texture;

	/**
	* Represents an instance of a mesh on the GPU
	* Useful for saving memory (only one copy needed)
	**/
	class GLMeshInstance
	{
	public:
		GLMeshInstance() = default;
		GLMeshInstance(const Mesh* mesh);

		void Load();
		void Unload();

		const Mesh* GetMesh() const;

		uint32 GetVAO() const;
		uint32 GetVBO() const;
		uint32 GetEBO() const;
		const GLTextureInfo* GetTextures() const;
		uint32 GetTextureCount() const;

	private:
		const Mesh* mesh;

		uint32 VAO, VBO, EBO;

		std::vector<GLTextureInfo> textures;

		bool isLoaded = false;

		void SetupTexture(const Texture* tex);
	};
}
