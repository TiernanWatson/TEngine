#pragma once
#include "Bindable.h"
#include <wrl.h>

namespace wrl = Microsoft::WRL;

namespace TEngine
{
	class DXShader : public Bindable
	{
	public:
		DXShader(D3D11Renderer& renderer, LPCWSTR file);

		ID3DBlob* GetBlob() const;

	protected:
		wrl::ComPtr<ID3DBlob> blob_;
	};
}
