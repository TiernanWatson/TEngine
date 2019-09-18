#pragma once
#include <vector>
#include "../../Core/PortableTypes.h"
#include "Vertex.h"
#include "../Shader/Shader.h"
#include "../Texture/Texture.h"

namespace TEngine
{
	class Mesh
	{
	public:
		std::vector<Vertex> vertices;
		std::vector<uint32> indices;
		std::vector<Texture> textures;
		
		Mesh(std::vector<Vertex> vertices, std::vector<uint32> indices, std::vector<Texture> textures);
		void Draw(Shader shader);

	private:
		uint32 VAO, VBO, EBO;
		
		void SetupMesh();
	};
}
