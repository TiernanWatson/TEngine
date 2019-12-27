#pragma once
#include "../../Core/PortableTypes.h"

namespace TEngine
{
	struct Texture;
	class Shader;

	class Material
	{
	public:
		Material(Texture* texture, uint32 shader);

		Texture* GetTexture() const;
		uint32 GetShader() const;

	private:
		// These are deleted elsewhere in the program
		Texture* texture;
		uint32 shader;
	};
}
