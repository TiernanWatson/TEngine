#include "DXPixelShader.h"
#include <d3dcompiler.h>

namespace TEngine
{
	DXPixelShader::DXPixelShader(D3D11Renderer& renderer, LPCWSTR file)
		: DXShader(renderer, file)
	{
		HRESULT hr;
		THROW_IF_FAIL(GetDevice()->CreatePixelShader(
			blob->GetBufferPointer(),
			blob->GetBufferSize(),
			nullptr,
			&pixelShader));
	}

	void DXPixelShader::Bind()
	{
		GetContext()->PSSetShader(pixelShader.Get(), nullptr, 0);
	}
}
