#include "DXIndexBuffer.h"

namespace TEngine 
{
	DXIndexBuffer::DXIndexBuffer(D3D11Renderer& renderer, const int* indices, int count)
		: Bindable(renderer)
	{
		D3D11_BUFFER_DESC bd = {};
		bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
		bd.ByteWidth = count * sizeof(int);
		bd.CPUAccessFlags = 0;
		bd.MiscFlags = 0;
		bd.StructureByteStride = sizeof(int);
		bd.Usage = D3D11_USAGE_DEFAULT;

		D3D11_SUBRESOURCE_DATA sr = {};
		sr.pSysMem = indices;

		HRESULT hr;
		THROW_IF_FAIL(GetDevice()->CreateBuffer(&bd, &sr, &indexBuffer));
	}

	void DXIndexBuffer::Bind()
	{
		GetContext()->IASetIndexBuffer(indexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);
	}
}
