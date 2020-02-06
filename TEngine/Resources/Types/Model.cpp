#include "Model.h"

namespace TEngine
{
	Model::Model()
		: Resource(0, "")
	{
	}

	Model::Model(std::vector<Mesh*> meshes, U32 rId, std::string path)
		: Resource(rId, path)
	{
		this->meshes_ = meshes;
	}

	const std::vector<Mesh*>& Model::GetMeshes() const
	{
		return meshes_;
	}
}
