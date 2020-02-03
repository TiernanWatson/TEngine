#pragma once
#include "../Core/PortableTypes.h"
#include "../Core/Math/Vector2.h"
#include "../Core/Math/Vector3.h"
#include "../Engine.h"
#include "../Render/D3D11/Bindables/DXPixelShader.h"
#include "../Render/D3D11/Bindables/DXVertexShader.h"
#include <string>

namespace TEngine
{
	class Font;

	class DebugUIRenderer
	{
	public:
		DebugUIRenderer();

		void StartUp();
		void VariableUpdate(float32 deltaTime);
		void FixedUpdate(float32 timeStep);
		void ShutDown();

	private:
		Font* font;
		RENDERER* renderer;

		DXVertexShader* vertexShader;
		DXPixelShader* pixelShader;

		void RenderText(std::string text,
						const Vector2& pos,
						float32 scale,
						const Vector3& color);
	};
}
