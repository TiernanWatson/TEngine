#include "DXVertexBuffer.h"
#include "../DXGraphicsExceptions.h"

namespace TEngine
{
	DXVertexBuffer::DXVertexBuffer(D3D11Renderer& renderer, const Vertex* vertices, maxint size)
		: Bindable(renderer)
	{
		D3D11_BUFFER_DESC desc = {};
		desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		desc.ByteWidth = size * sizeof(Vertex);
		desc.CPUAccessFlags = 0;
		desc.MiscFlags = 0;
		desc.StructureByteStride = sizeof(Vertex);
		desc.Usage = D3D11_USAGE_DEFAULT;

		D3D11_SUBRESOURCE_DATA sr = {};
		sr.pSysMem = vertices;

		HRESULT hr;
		THROW_IF_FAIL(GetDevice()->CreateBuffer(&desc, &sr, &vertexBuffer));
	}

	void DXVertexBuffer::Bind()
	{
		const UINT stride = sizeof(Vertex);
		const UINT offset = 0;
		GetContext()->IASetVertexBuffers(0, 1, vertexBuffer.GetAddressOf(), &stride, &offset);
	}
}
