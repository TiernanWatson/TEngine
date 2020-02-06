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
			std::vector<U32> indices,
			std::vector<Material*> materials,
			U32 r_id,
			std::string path
		);

		const std::vector<Vertex>& GetVertices() const;
		const std::vector<U32>& GetIndices() const;
		const std::vector<Material*>& GetMaterials() const;

	protected:
		std::vector<Vertex> vertices_;
		std::vector<U32> indices_;
		std::vector<Material*> materials_;
	};
}
