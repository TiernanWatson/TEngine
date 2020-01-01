#include "Material.h"

namespace TEngine
{
	Material::Material()
		: diffuse(nullptr), specular(nullptr), normal(nullptr), height(nullptr)
	{
	}

	Material::Material(Texture* diffuse, Texture* specular, Texture* normal, Texture* height, uint32 rId, std::string path)
		: diffuse(diffuse), specular(specular), normal(normal), height(height), Resource(rId, path)
	{
	}

	Texture* Material::GetDiffuse() const
	{
		return diffuse;
	}

	Texture* Material::GetSpecular() const
	{
		return specular;
	}
	
	Texture* Material::GetNormal() const
	{
		return normal;
	}

	Texture* Material::GetHeight() const
	{
		return height;
	}
}
