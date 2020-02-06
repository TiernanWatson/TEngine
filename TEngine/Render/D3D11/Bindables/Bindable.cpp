#include "Bindable.h"

namespace TEngine
{
	Bindable::Bindable(D3D11Renderer& renderer)
		: renderer_(renderer)
	{
	}

	ID3D11Device* Bindable::GetDevice() const
	{
		return renderer_.device_.Get();
	}

	ID3D11DeviceContext* Bindable::GetContext() const
	{
		return renderer_.context_.Get();
	}
}
