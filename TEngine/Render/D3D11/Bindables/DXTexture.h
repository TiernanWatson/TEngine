#pragma once
#include "Bindable.h"
#include "../../../Resources/Types/Texture.h"
#include <wrl.h>

namespace wrl = Microsoft::WRL;

namespace TEngine
{
	class DXTexture : public Bindable
	{
	public:
		DXTexture(D3D11Renderer& renderer, Texture* texture);

		void Bind() override;

		static DXTexture* GetBlank(D3D11Renderer& renderer);

	private:
		DXTexture(D3D11Renderer& renderer);

		wrl::ComPtr<ID3D11ShaderResourceView> texView;
	};
}
