#include "Mesh.h"
#include <glad/glad.h>
#include <glfw3.h>
#include "Vertex.h"
#include "../Texture/Texture.h"
#include "../Shader/Shader.h"

namespace TEngine
{
	Mesh::Mesh(std::vector<Vertex> vertices, std::vector<uint32> indices, std::vector<Texture> textures)
	{
		this->vertices = vertices;
		this->indices = indices;
		this->textures = textures;
	}
}
