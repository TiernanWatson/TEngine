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
			U32 r_id,
			std::string path
		);

		Texture* GetDiffuse() const;
		Texture* GetSpecular() const;
		Texture* GetNormal() const;
		Texture* GetHeight() const;

	protected:
		Texture* diffuse_;
		Texture* specular_;
		Texture* normal_;
		Texture* height_;
	};
}
