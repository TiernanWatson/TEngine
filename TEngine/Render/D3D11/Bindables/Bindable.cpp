#include "Bindable.h"

namespace TEngine
{
	Bindable::Bindable(D3D11Renderer& renderer)
		: renderer(renderer)
	{
	}

	ID3D11Device* Bindable::GetDevice() const
	{
		return renderer.device.Get();
	}

	ID3D11DeviceContext* Bindable::GetContext() const
	{
		return renderer.context.Get();
	}
}
