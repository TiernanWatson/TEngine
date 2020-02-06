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
			blob_->GetBufferPointer(),
			blob_->GetBufferSize(),
			nullptr,
			&vertex_shader_));
	}

	void DXVertexShader::Bind()
	{
		GetContext()->VSSetShader(vertex_shader_.Get(), nullptr, 0);
	}
}
