#pragma once
#include "DXShader.h"

namespace TEngine
{
	class DXPixelShader : public DXShader
	{
	public:
		DXPixelShader(D3D11Renderer& renderer, LPCWSTR file);

		void Bind() override;

	private:
		wrl::ComPtr<ID3D11PixelShader> pixel_shader_;
	};
}
