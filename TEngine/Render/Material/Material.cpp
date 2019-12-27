#include "Material.h"

namespace TEngine
{
	Material::Material(Texture* texture, uint32 shader)
	{
		this->texture = texture;
		this->shader = shader;
	}

	Texture* Material::GetTexture() const
	{
		return texture;
	}

	uint32 Material::GetShader() const
	{
		return shader;
	}
}
