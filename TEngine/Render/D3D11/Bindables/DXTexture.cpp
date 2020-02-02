#include "DXTexture.h"

namespace TEngine
{
	DXTexture::DXTexture(D3D11Renderer& renderer, Texture* texture)
		: Bindable(renderer)
	{
		this->texture = texture;

		if (texture == nullptr)
		{
			return;
		}

		HRESULT hr;

		D3D11_TEXTURE2D_DESC texDesc = {};
		texDesc.Width = texture->GetWidth();
		texDesc.Height = texture->GetHeight();
		texDesc.MipLevels = 1;
		texDesc.ArraySize = 1;
		texDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		texDesc.SampleDesc.Count = 1;
		texDesc.SampleDesc.Quality = 0;
		texDesc.Usage = D3D11_USAGE_DEFAULT;
		texDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
		texDesc.CPUAccessFlags = 0;
		texDesc.MiscFlags = 0;

		D3D11_SUBRESOURCE_DATA sr = {};
		sr.pSysMem = texture->GetDataPtr();
		sr.SysMemPitch = texture->GetWidth() * 4;
		sr.SysMemSlicePitch = 0;

		wrl::ComPtr<ID3D11Texture2D> texture2D;
		THROW_IF_FAIL(GetDevice()->CreateTexture2D(&texDesc, &sr, &texture2D));

		/*GetContext()->UpdateSubresource(
			texture2D.Get(), 0u, nullptr, texture.GetDataPtr(), texture.GetWidth() * 3, 0u
		);*/

		// Create the resource view on the texture
		D3D11_SHADER_RESOURCE_VIEW_DESC viewDesc = {};
		viewDesc.Format = texDesc.Format;
		viewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		viewDesc.Texture2D.MostDetailedMip = 0;
		viewDesc.Texture2D.MipLevels = 1;
		THROW_IF_FAIL(GetDevice()->CreateShaderResourceView(
			texture2D.Get(), &viewDesc, &texView
		));

		// Generate the mip chain using the gpu rendering pipeline
		//GetContext()->GenerateMips(texView.Get());
	}

	void DXTexture::Bind()
	{
		GetContext()->PSSetShaderResources(0, 1u, texView.GetAddressOf());
	}
}
