#pragma once
#include "Bindable.h"
#include <wrl.h>

namespace wrl = Microsoft::WRL;

namespace TEngine
{
	class DXInputLayout : public Bindable
	{
	public:
		DXInputLayout(D3D11Renderer& renderer,
			const D3D11_INPUT_ELEMENT_DESC* desc,
			UINT num_elements,
			ID3DBlob* shader_blob);

		void Bind() override;

	private:
		wrl::ComPtr<ID3D11InputLayout> input_layout_;
	};
}
