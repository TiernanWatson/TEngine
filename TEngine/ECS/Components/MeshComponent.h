#pragma once
#include "../../Render/Models/Mesh.h"

namespace TEngine
{
	class Mesh;

	struct MeshComponent
	{
		uint32 VAO;
		uint32 VBO;
		uint32 EBO;
		uint32 texture;
		maxint indexCount;
		Mesh* mesh;
	};
}
