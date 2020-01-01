#include "GLMeshInstance.h"
#include <glad/glad.h>
#include <glfw3.h>
#include "Vertex.h"
#include "../Resources/Types/Mesh.h"
#include "../Resources/Types/Texture.h"
#include "../Resources/Types/Material.h"

namespace TEngine
{
	GLMeshInstance::GLMeshInstance(const Mesh* mesh)
		: mesh(mesh), VAO(0), VBO(0), EBO(0)
	{
	}

	void GLMeshInstance::Load()
	{
		assert(!isLoaded);

		//
		// Setup mesh VAO, VBO and EBO and pointers first
		//

		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);

		// Copy info to VRAM
		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, mesh->GetVertices().size() * sizeof(Vertex), &mesh->GetVertices()[0], GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh->GetIndices().size() * sizeof(uint32), &mesh->GetIndices()[0], GL_STATIC_DRAW);

		// Create attribute pointers
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, tangent));
		glEnableVertexAttribArray(3);
		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, bitangent));
		glEnableVertexAttribArray(4);
		glVertexAttribPointer(4, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, textCoord));

		// Unbind
		glBindVertexArray(0);

		//
		// Then setup textures
		//

		SetupTexture(mesh->GetMaterials()[0]->GetDiffuse());
		SetupTexture(mesh->GetMaterials()[0]->GetSpecular());
		SetupTexture(mesh->GetMaterials()[0]->GetNormal());
		SetupTexture(mesh->GetMaterials()[0]->GetHeight());

		isLoaded = true;
	}

	void GLMeshInstance::Unload()
	{
		assert(isLoaded);

		isLoaded = false;
	}

	const Mesh* GLMeshInstance::GetMesh() const
	{
		return mesh;
	}

	uint32 GLMeshInstance::GetVAO() const
	{
		assert(isLoaded);

		return VAO;
	}

	uint32 GLMeshInstance::GetVBO() const
	{
		assert(isLoaded);

		return VBO;
	}

	uint32 GLMeshInstance::GetEBO() const
	{
		assert(isLoaded);

		return EBO;
	}

	const GLTextureInfo* GLMeshInstance::GetTextures() const
	{
		return textures.data();
	}

	uint32 GLMeshInstance::GetTextureCount() const
	{
		return textures.size();
	}

	void GLMeshInstance::SetupTexture(const Texture* tex)
	{
		if (tex == nullptr) return;

		GLTextureInfo texInfo;
		glGenTextures(1, &texInfo.id);

		GLenum format;
		switch (tex->GetFormat())
		{
		case TexFormat::R:
			format = GL_RED;
			break;
		case TexFormat::RGB:
			format = GL_RGB;
			break;
		case TexFormat::RGBA:
			format = GL_RGBA;
			break;
		default:
			throw std::exception("Unrecognised texture format!");
		}

		texInfo.type = tex->GetType();

		CONSOLE_PRINT("Adding tex: " + tex->GetPath())

		glBindTexture(GL_TEXTURE_2D, texInfo.id);
		glTexImage2D(GL_TEXTURE_2D, 0, format, tex->GetWidth(), tex->GetHeight(),
			0, format, GL_UNSIGNED_BYTE, tex->GetDataPtr());

		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		textures.push_back(texInfo);
	}
}
