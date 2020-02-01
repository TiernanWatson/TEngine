#include "DXShader.h"
#include <d3dcompiler.h>

namespace TEngine
{
	DXShader::DXShader(D3D11Renderer& renderer, LPCWSTR file)
		: Bindable(renderer)
	{
		HRESULT hr;
		THROW_IF_FAIL(D3DReadFileToBlob(file, &blob));
	}

	ID3DBlob* DXShader::GetBlob() const
	{
		return blob.Get();
	}
}
