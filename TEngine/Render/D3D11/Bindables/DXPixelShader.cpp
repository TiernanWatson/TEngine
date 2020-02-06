#include "DXPixelShader.h"
#include <d3dcompiler.h>

namespace TEngine
{
	DXPixelShader::DXPixelShader(D3D11Renderer& renderer, LPCWSTR file)
		: DXShader(renderer, file)
	{
		HRESULT hr;
		THROW_IF_FAIL(GetDevice()->CreatePixelShader(
			blob_->GetBufferPointer(),
			blob_->GetBufferSize(),
			nullptr,
			&pixel_shader_));
	}

	void DXPixelShader::Bind()
	{
		GetContext()->PSSetShader(pixel_shader_.Get(), nullptr, 0);
	}
}
