#include "DXVertexShader.h"
#include <d3d11.h>
#include <d3dcompiler.h>

namespace TEngine
{
	DXVertexShader::DXVertexShader(D3D11Renderer& renderer, LPCWSTR file)
		: DXShader(renderer, file)
	{
		HRESULT hr;
		THROW_IF_FAIL(GetDevice()->CreateVertexShader(
			blob->GetBufferPointer(),
			blob->GetBufferSize(),
			nullptr,
			&vertexShader));
	}

	void DXVertexShader::Bind()
	{
		GetContext()->VSSetShader(vertexShader.Get(), nullptr, 0);
	}
}
