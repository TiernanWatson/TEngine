#include "Mesh.h"

namespace TEngine
{
	Mesh::Mesh()
	{
	}

	Mesh::Mesh(std::vector<Vertex> vertices, std::vector<U32> indices, std::vector<Material*> materials, U32 rId, std::string path)
		: Resource(rId, path)
	{
		this->vertices_ = vertices;
		this->indices_ = indices;
		this->materials_ = materials;
	}

	const std::vector<Vertex>& Mesh::GetVertices() const
	{
		return vertices_;
	}

	const std::vector<U32>& Mesh::GetIndices() const
	{
		return indices_;
	}

	const std::vector<Material*>& Mesh::GetMaterials() const
	{
		return materials_;
	}
}
