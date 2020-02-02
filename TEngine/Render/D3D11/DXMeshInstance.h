#pragma once
#include <d3d11.h>
#include "Bindables/DXVertexBuffer.h"
#include "Bindables/DXIndexBuffer.h"
#include "Bindables/DXTexture.h"

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
		DXTexture texture;

		int indexCount;
		
		D3D11Renderer& renderer;
	};
}
