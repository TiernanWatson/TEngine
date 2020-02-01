#include "DXMeshInstance.h"
#include "../../Resources/Types/Mesh.h"

namespace TEngine
{
	DXMeshInstance::DXMeshInstance(D3D11Renderer& renderer, const Mesh* mesh) :
		vertexBuffer(renderer, mesh->GetVertices().data(), (maxint)mesh->GetVertices().size()),
		indexBuffer(renderer, (int*)mesh->GetIndices().data(), (int)mesh->GetIndices().size()),
		renderer(renderer), indexCount((int)mesh->GetIndices().size())
	{
	}

	void DXMeshInstance::Draw()
	{
		vertexBuffer.Bind();
		indexBuffer.Bind();

		renderer.DrawIndexed(indexCount);
	}
}
