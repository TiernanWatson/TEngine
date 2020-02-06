#include "DXSampler.h"

namespace TEngine
{
	DXSampler::DXSampler(D3D11Renderer& renderer)
		: Bindable(renderer)
	{
		D3D11_SAMPLER_DESC desc = {};
		desc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
		desc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
		desc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
		desc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;

		HRESULT hr;
		THROW_IF_FAIL(GetDevice()->CreateSamplerState(&desc, &sampler_));
	}

	void DXSampler::Bind()
	{
		GetContext()->PSSetSamplers(0, 1, sampler_.GetAddressOf());
	}
}
