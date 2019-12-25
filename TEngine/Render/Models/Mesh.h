#pragma once
#include <vector>
#include "../../Core/PortableTypes.h"
#include "Vertex.h"
#include "../Shader/Shader.h"
#include "../Texture/Texture.h"

namespace TEngine
{
	class Material;

	class Mesh
	{
	public:
		std::vector<Vertex> vertices;
		std::vector<uint32> indices;
		std::vector<Texture> textures;
		std::vector<Material*> materials;
		
		Mesh(std::vector<Vertex> vertices, std::vector<uint32> indices, std::vector<Texture> textures);
	};
}
