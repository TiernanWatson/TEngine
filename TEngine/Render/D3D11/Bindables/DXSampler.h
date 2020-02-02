#pragma once
#include "Bindable.h"
#include <wrl.h>

namespace wrl = Microsoft::WRL;

namespace TEngine
{
	class DXSampler : public Bindable
	{
	public:
		DXSampler(D3D11Renderer& renderer);

		void Bind() override;

	private:
		wrl::ComPtr<ID3D11SamplerState> sampler;
	};
}
