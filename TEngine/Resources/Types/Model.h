#pragma once
#include "../Resource.h"
#include <vector>

namespace TEngine
{
	class Mesh;

	class Model : public Resource
	{
	public:
		Model();
		Model(std::vector<Mesh*> meshes, U32 r_id, std::string path);

		const std::vector<Mesh*>& GetMeshes() const;

	protected:
		std::vector<Mesh*> meshes_;
	};
}
