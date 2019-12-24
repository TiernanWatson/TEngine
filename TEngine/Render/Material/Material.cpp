#include "Material.h"

namespace TEngine
{
	Material::Material(Texture* texture, Shader* shader)
	{
		this->texture = texture;
		this->shader = shader;
	}

	Texture* Material::GetTexture() const
	{
		return texture;
	}

	Shader* Material::GetShader() const
	{
		return shader;
	}
}
