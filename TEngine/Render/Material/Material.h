#pragma once
#include "../../Core/PortableTypes.h"

namespace TEngine
{
	class Texture;
	class Shader;

	class Material
	{
	public:
		Material(Texture* texture, Shader* shader);

		Texture* GetTexture() const;
		Shader* GetShader() const;

	private:
		// These are deleted elsewhere in the program
		Texture* texture;
		Shader* shader;
	};
}
