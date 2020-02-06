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
		void VariableUpdate(F32 delta_time);
		void FixedUpdate(F32 time_step);
		void ShutDown();

	private:
		Font* font_;
		RENDERER* renderer_;

		DXVertexShader* vertex_shader_;
		DXPixelShader* pixel_shader_;

		void RenderText(std::string text,
						const Vector2& pos,
						F32 scale,
						const Vector3& color);
	};
}
