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
		DXVertexBuffer vertex_buffer_;
		DXIndexBuffer index_buffer_;
		DXTexture texture_;

		int index_count_;
		
		D3D11Renderer& renderer_;
	};
}
