#include "DXMeshInstance.h"
#include "../../Resources/Types/Mesh.h"
#include "../../Resources/Types/Material.h"

namespace TEngine
{
	DXMeshInstance::DXMeshInstance(D3D11Renderer& renderer, const Mesh* mesh) :
		vertex_buffer_(renderer, mesh->GetVertices().data(), (USIZE)mesh->GetVertices().size()),
		index_buffer_(renderer, (int*)mesh->GetIndices().data(), (int)mesh->GetIndices().size()),
		texture_(renderer, mesh->GetMaterials()[0]->GetDiffuse()),
		renderer_(renderer), index_count_((int)mesh->GetIndices().size())
	{
	}

	void DXMeshInstance::Draw()
	{
		vertex_buffer_.Bind();
		index_buffer_.Bind();
		texture_.Bind();

		renderer_.DrawIndexed(index_count_);
	}
}
