#include "DXInputLayout.h"

namespace TEngine
{
	DXInputLayout::DXInputLayout(D3D11Renderer& renderer, 
		const D3D11_INPUT_ELEMENT_DESC* desc, 
		UINT numElements, 
		ID3DBlob* shaderBlob)
		: Bindable(renderer)
	{
		HRESULT hr;
		THROW_IF_FAIL(GetDevice()->CreateInputLayout(desc, numElements, 
			shaderBlob->GetBufferPointer(), shaderBlob->GetBufferSize(), 
			&inputLayout));
	}

	void DXInputLayout::Bind()
	{
		GetContext()->IASetInputLayout(inputLayout.Get());
	}
}
