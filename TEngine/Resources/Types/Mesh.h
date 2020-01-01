#pragma once
#include "../Resource.h"
#include "../../Render/Vertex.h"
#include <vector>

namespace TEngine
{
	class Material;

	class Mesh : public Resource
	{
	public:
		Mesh();
		Mesh(
			std::vector<Vertex> vertices,
			std::vector<uint32> indices,
			std::vector<Material*> materials,
			uint32 rId,
			std::string path
		);

		const std::vector<Vertex>& GetVertices() const;
		const std::vector<uint32>& GetIndices() const;
		const std::vector<Material*>& GetMaterials() const;

	protected:
		std::vector<Vertex> vertices;
		std::vector<uint32> indices;
		std::vector<Material*> materials;
	};
}
