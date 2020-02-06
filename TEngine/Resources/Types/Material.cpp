#include "Material.h"

namespace TEngine
{
	Material::Material()
		: diffuse_(nullptr), specular_(nullptr), normal_(nullptr), height_(nullptr)
	{
	}

	Material::Material(Texture* diffuse, Texture* specular, Texture* normal, Texture* height, U32 rId, std::string path)
		: diffuse_(diffuse), specular_(specular), normal_(normal), height_(height), Resource(rId, path)
	{
	}

	Texture* Material::GetDiffuse() const
	{
		return diffuse_;
	}

	Texture* Material::GetSpecular() const
	{
		return specular_;
	}
	
	Texture* Material::GetNormal() const
	{
		return normal_;
	}

	Texture* Material::GetHeight() const
	{
		return height_;
	}
}
