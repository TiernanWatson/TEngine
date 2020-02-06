#pragma once
#include "Bindable.h"
#include "../../Vertex.h"
#include <d3d11.h>
#include <wrl.h>

namespace wrl = Microsoft::WRL;

namespace TEngine
{
	class DXVertexBuffer : public Bindable
	{
	public:
		DXVertexBuffer() = delete;
		DXVertexBuffer(D3D11Renderer& renderer, const Vertex* vertices, USIZE size);

		void Bind() override;

	private:
		wrl::ComPtr<ID3D11Buffer> vertex_buffer_;
	};
}
