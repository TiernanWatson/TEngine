#pragma once
#include "../Resource.h"

namespace TEngine
{
	class Texture;

	class Material : public Resource
	{
	public:
		Material();
		Material(
			Texture* diffuse, 
			Texture* specular, 
			Texture* normal, 
			Texture* height,
			uint32 rId,
			std::string path
		);

		Texture* GetDiffuse() const;
		Texture* GetSpecular() const;
		Texture* GetNormal() const;
		Texture* GetHeight() const;

	protected:
		Texture* diffuse;
		Texture* specular;
		Texture* normal;
		Texture* height;
	};
}
