#pragma once
#include "../D3D11Renderer.h"

namespace TEngine
{
	class Bindable
	{
	public:
		Bindable(D3D11Renderer& renderer);
		virtual void Bind() = 0;

	protected:
		ID3D11Device* GetDevice() const;
		ID3D11DeviceContext* GetContext() const;

	private:
		D3D11Renderer& renderer;
	};
}
