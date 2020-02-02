#include "DXMeshInstance.h"
#include "../../Resources/Types/Mesh.h"
#include "../../Resources/Types/Material.h"

namespace TEngine
{
	DXMeshInstance::DXMeshInstance(D3D11Renderer& renderer, const Mesh* mesh) :
		vertexBuffer(renderer, mesh->GetVertices().data(), (maxint)mesh->GetVertices().size()),
		indexBuffer(renderer, (int*)mesh->GetIndices().data(), (int)mesh->GetIndices().size()),
		texture(renderer, mesh->GetMaterials()[0]->GetDiffuse()),
		renderer(renderer), indexCount((int)mesh->GetIndices().size())
	{
	}

	void DXMeshInstance::Draw()
	{
		vertexBuffer.Bind();
		indexBuffer.Bind();
		texture.Bind();

		renderer.DrawIndexed(indexCount);
	}
}
