#pragma once
#include "Bindable.h"
#include <wrl.h>

namespace wrl = Microsoft::WRL;

namespace TEngine
{
	class DXIndexBuffer : public Bindable
	{
	public:
		DXIndexBuffer(D3D11Renderer& renderer, const int* indices, int count);

		void Bind() override;

	private:
		wrl::ComPtr<ID3D11Buffer> indexBuffer;
	};
}
