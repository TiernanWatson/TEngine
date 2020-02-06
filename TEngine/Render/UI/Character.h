#pragma once
#include "../../Core/PortableTypes.h"
#include "../../Core/Math/Vector2Int.h"
#ifdef DIRECTX
#include "../D3D11/Bindables/DXTexture.h"
#endif

namespace TEngine
{
	struct Character
	{
#ifdef DIRECTX
		DXTexture* dx_texture_;
#elif defined(OPENGL)
		uint32 textureID;
#endif
		//Texture* texture_;
		U32 advance_;
		Vector2Int bearing_;
		Vector2Int size_;
	};
}
