#include "DXTexture.h"

namespace TEngine
{
	DXTexture::DXTexture(D3D11Renderer& renderer, Texture* texture)
		: Bindable(renderer)
	{
		if (texture == nullptr)
		{
			OutputDebugString("Was nullptr\n");
			return;
		}

		HRESULT hr;

		TexFormat format = texture->GetFormat();
		DXGI_FORMAT dxFormat;
		switch (format)
		{
		case TexFormat::R:
			dxFormat = DXGI_FORMAT_R8_UNORM;
			break;
		case TexFormat::RGBA:
			dxFormat = DXGI_FORMAT_R8G8B8A8_UNORM;
			break;
		default:
			throw EXCEPTION("DXTexture could not use specified TexFormat");
		}

		D3D11_TEXTURE2D_DESC texDesc = {};
		texDesc.Width = texture->GetWidth() > 0 ? texture->GetWidth() : 1;
		texDesc.Height = texture->GetHeight() > 0 ? texture->GetHeight() : 1;
		texDesc.MipLevels = 1;
		texDesc.ArraySize = 1;
		texDesc.Format = dxFormat;
		texDesc.SampleDesc.Count = 1;
		texDesc.SampleDesc.Quality = 0;
		texDesc.Usage = D3D11_USAGE_DEFAULT;
		texDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
		texDesc.CPUAccessFlags = 0;
		texDesc.MiscFlags = 0;

		UINT texelWidth;
		switch (format)
		{
		case TexFormat::R:
			texelWidth = 1;
			break;
		case TexFormat::RGBA:
			texelWidth = 4;
			break;
		default:
			throw EXCEPTION("DXTexture could not use specified TexFormat");
		}

		wrl::ComPtr<ID3D11Texture2D> texture2D;
		if (texture->GetDataPtr() != nullptr) 
		{
			OutputDebugString("was NOT null dataptr\n");

			D3D11_SUBRESOURCE_DATA sr = {};
			sr.pSysMem = texture->GetDataPtr();
			sr.SysMemPitch = texture->GetWidth() * texelWidth;
			sr.SysMemSlicePitch = 0;

			THROW_IF_FAIL(GetDevice()->CreateTexture2D(&texDesc, &sr, &texture2D));
		}
		else
		{
			THROW_IF_FAIL(GetDevice()->CreateTexture2D(&texDesc, NULL, &texture2D));
		}

		// Create the resource view on the dxTexture
		D3D11_SHADER_RESOURCE_VIEW_DESC viewDesc = {};
		viewDesc.Format = texDesc.Format;
		viewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		viewDesc.Texture2D.MostDetailedMip = 0;
		viewDesc.Texture2D.MipLevels = 1;
		THROW_IF_FAIL(GetDevice()->CreateShaderResourceView(
			texture2D.Get(), &viewDesc, &texView
		));
	}

	DXTexture::DXTexture(D3D11Renderer& renderer)
		: Bindable(renderer)
	{
		HRESULT hr;

		D3D11_TEXTURE2D_DESC texDesc = {};
		texDesc.Width = 1;
		texDesc.Height = 1;
		texDesc.MipLevels = 1;
		texDesc.ArraySize = 1;
		texDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		texDesc.SampleDesc.Count = 1;
		texDesc.SampleDesc.Quality = 0;
		texDesc.Usage = D3D11_USAGE_DEFAULT;
		texDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
		texDesc.CPUAccessFlags = 0;
		texDesc.MiscFlags = 0;

		wrl::ComPtr<ID3D11Texture2D> texture2D;
		THROW_IF_FAIL(GetDevice()->CreateTexture2D(&texDesc, NULL, &texture2D));

		// Create the resource view on the dxTexture
		D3D11_SHADER_RESOURCE_VIEW_DESC viewDesc = {};
		viewDesc.Format = texDesc.Format;
		viewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		viewDesc.Texture2D.MostDetailedMip = 0;
		viewDesc.Texture2D.MipLevels = 1;
		THROW_IF_FAIL(GetDevice()->CreateShaderResourceView(
			texture2D.Get(), &viewDesc, &texView
		));
	}

	void DXTexture::Bind()
	{
		GetContext()->PSSetShaderResources(0, 1u, texView.GetAddressOf());
	}

	DXTexture* DXTexture::GetBlank(D3D11Renderer& renderer)
	{
		static DXTexture def(renderer);
		return &def;
	}
}
