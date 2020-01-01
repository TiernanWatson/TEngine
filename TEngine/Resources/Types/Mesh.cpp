#include "Mesh.h"

namespace TEngine
{
	Mesh::Mesh()
	{
	}

	Mesh::Mesh(std::vector<Vertex> vertices, std::vector<uint32> indices, std::vector<Material*> materials, uint32 rId, std::string path)
		: Resource(rId, path)
	{
		this->vertices = vertices;
		this->indices = indices;
		this->materials = materials;
	}

	const std::vector<Vertex>& Mesh::GetVertices() const
	{
		return vertices;
	}

	const std::vector<uint32>& Mesh::GetIndices() const
	{
		return indices;
	}

	const std::vector<Material*>& Mesh::GetMaterials() const
	{
		return materials;
	}
}
