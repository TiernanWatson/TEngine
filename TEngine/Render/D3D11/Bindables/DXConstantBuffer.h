#pragma once
#include "Bindable.h"
#include "../D3D11Renderer.h"
#include <wrl.h>

namespace wrl = Microsoft::WRL;

namespace TEngine
{
	template<typename T>
	class DXConstantBuffer : public Bindable
	{
	public:
		DXConstantBuffer(D3D11Renderer& renderer, T& data);

		void Update(T& data);

	protected:
		wrl::ComPtr<ID3D11Buffer> const_buffer_;
	};

	template<typename T>
	DXConstantBuffer<T>::DXConstantBuffer(D3D11Renderer& renderer, T& data)
		: Bindable(renderer)
	{
		HRESULT hr;

		D3D11_BUFFER_DESC cbd = {};
		cbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		cbd.Usage = D3D11_USAGE_DYNAMIC;
		cbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		cbd.MiscFlags = 0;
		cbd.ByteWidth = sizeof(T);
		cbd.StructureByteStride = 0;

		D3D11_SUBRESOURCE_DATA csr = {};
		csr.pSysMem = &data;

		THROW_IF_FAIL(GetDevice()->CreateBuffer(&cbd, &csr, &const_buffer_));
	}

	template<typename T>
	inline void DXConstantBuffer<T>::Update(T& data)
	{
		HRESULT hr;

		D3D11_MAPPED_SUBRESOURCE mapped;
		THROW_IF_FAIL(GetContext()->Map(
			const_buffer_.Get(),
			0,
			D3D11_MAP_WRITE_DISCARD,
			0,
			&mapped
		));

		memcpy(mapped.pData, &data, sizeof(T));
		GetContext()->Unmap(const_buffer_.Get(), 0);
	}

	/*
	* Vertex Shader CB
	*/

	template<typename T>
	class DXVSConstantBuffer : public DXConstantBuffer<T>
	{
	public:
		DXVSConstantBuffer(D3D11Renderer& renderer, T& data)
			: DXConstantBuffer<T>(renderer, data) {}

		void Bind() override
		{
			Bindable::GetContext()->VSSetConstantBuffers(0, 1, 
				DXConstantBuffer<T>::const_buffer_.GetAddressOf());
		}
	};

	/*
	* Pixel Shader CB
	*/

	template<typename T>
	class DXPSConstantBuffer : public DXConstantBuffer<T>
	{
	public:
		DXPSConstantBuffer(D3D11Renderer& renderer, T& data)
			: DXConstantBuffer<T>(renderer, data) {}

		void Bind() override;
	};

	template<typename T>
	void DXPSConstantBuffer<T>::Bind()
	{
		Bindable::GetContext()->PSSetConstantBuffers(0, 1, 
			DXConstantBuffer<T>::const_buffer_.GetAddressOf());
	}
}
