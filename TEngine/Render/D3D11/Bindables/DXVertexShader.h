#pragma once
#include "DXShader.h"

namespace TEngine
{
	class DXVertexShader : public DXShader
	{
	public:
		DXVertexShader(D3D11Renderer& renderer, LPCWSTR file);

		void Bind() override;

	private:
		wrl::ComPtr<ID3D11VertexShader> vertexShader;
	};
}
