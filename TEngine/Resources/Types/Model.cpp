#include "Model.h"

namespace TEngine
{
	Model::Model()
		: Resource(0, "")
	{
	}

	Model::Model(std::vector<Mesh*> meshes, uint32 rId, std::string path)
		: Resource(rId, path)
	{
		this->meshes = meshes;
	}

	const std::vector<Mesh*>& Model::GetMeshes() const
	{
		return meshes;
	}
}
