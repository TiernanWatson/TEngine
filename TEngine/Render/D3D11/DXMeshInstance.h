#pragma once
#include <d3d11.h>
#include "Bindables/DXVertexBuffer.h"
#include "Bindables/DXIndexBuffer.h"

namespace TEngine
{
	class Mesh;

	class DXMeshInstance
	{
	public:
		DXMeshInstance(D3D11Renderer& renderer, const Mesh* mesh);
		~DXMeshInstance() = default;

		void Draw();

	private:
		DXVertexBuffer vertexBuffer;
		DXIndexBuffer indexBuffer;
		int indexCount;
		
		D3D11Renderer& renderer;
	};
}
