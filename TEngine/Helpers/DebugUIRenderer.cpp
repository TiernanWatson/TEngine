#ifdef _DEBUG
#include "DebugUIRenderer.h"
#include "Debug.h"
#include "../Core/Math/Matrix4.h"
#include "../Core/IO/FileSystem.h"
#include "../Render/UI/Character.h"
#include "../Render/UI/Font.h"
#include "../Render/Material/Shaders.h"
#include "../Render/D3D11/Bindables/DXConstantBuffer.h"
#include "../Render/D3D11/Bindables/DXVertexBuffer.h"
#include "../Render/D3D11/Bindables/DXInputLayout.h"
#include <vector>

namespace TEngine
{
	DebugUIRenderer::DebugUIRenderer()
		: font(nullptr)
	{
	}

	void DebugUIRenderer::StartUp()
	{
		this->font = Font::GetDefaultFont();
		this->renderer = &Engine::Get().GetRenderer();

		vertexShader = new DXVertexShader(*renderer, L"TextVertexShader.cso");
		pixelShader = new DXPixelShader(*renderer, L"TextPixelShader.cso");
	}

	void DebugUIRenderer::VariableUpdate(float32 deltaTime)
	{
		vertexShader->Bind();
		pixelShader->Bind();
		
		struct ConstBuff
		{
			Matrix4 projection;
		};
		
		ConstBuff cdata;
		cdata.projection = Matrix4::Orthographic(-1.f, 1.f, 0.0f, 1024.f, 0.0f, 768.f).Transpose();

		DXVSConstantBuffer<ConstBuff> cbuff(*renderer, cdata);
		cbuff.Bind();

		float32 FPS = 1.f / deltaTime;
		std::string title = "Odyssey Debug Build: " + std::to_string((int)FPS) + "FPS";

		RenderText(title, Vector2(0.f, 750.f), 1.f, Vector3(1.f, 1.f, 1.f));

		float32 distance = 20.f;
		for (int i = 0; i < Debug::screenMessages.size(); i++)
		{
			RenderText(Debug::screenMessages[i], 
				Vector2(0.f, 700.f - i * distance), 
				1.f, 
				Vector3(1.f, 1.f, 1.f));
		}
	}

	void DebugUIRenderer::FixedUpdate(float32 timeStep)
	{
		// TODO: Some method of fixed update logging
	}

	void DebugUIRenderer::ShutDown()
	{
		this->font = nullptr;
		this->renderer = nullptr;
	}

	void DebugUIRenderer::RenderText(std::string text,
								const Vector2& pos,
								float32 scale,
								const Vector3& color)
	{
		float32 x = pos.x;
		float32 y = pos.y;

		// Render character by character
		std::string::const_iterator c;
		for (c = text.begin(); c != text.end(); c++)
		{
			Character fontChar = font->GetCharacter(*c);

			float32 xpos = x + fontChar.bearing.x * scale;
			float32 ypos = y - (fontChar.size.y - fontChar.bearing.y) * scale;
			float32 w = fontChar.size.x * scale;
			float32 h = fontChar.size.y * scale;

			Vertex vertices[6] = {
				{ Vector3(xpos, ypos + h, 0.f), Vector3(), Vector2(0.0, 0.0) },
				{ Vector3(xpos + w, ypos, 0.f), Vector3(), Vector2(1.0, 1.0) },
				{ Vector3(xpos, ypos, 0.f), Vector3(), Vector2(0.0, 1.0) },

				{ Vector3(xpos, ypos + h, 0.f), Vector3(), Vector2(0.0, 0.0) },
				{ Vector3(xpos + w, ypos + h, 0.f), Vector3(), Vector2(1.0, 0.0) },
				{ Vector3(xpos + w, ypos, 0.f), Vector3(), Vector2(1.0, 1.0) }
			};

			DXVertexBuffer vertexBuffer(Engine::Get().GetRenderer(), vertices, 6);
			vertexBuffer.Bind();

			fontChar.dxTexture->Bind();
			renderer->Draw(6);

			// Advance is 1/64th of a pixel so multiply by 64
			x += (fontChar.advance >> 6) * scale;
		}
	}
}
#endif
