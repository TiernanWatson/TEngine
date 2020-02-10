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
#include "../Core/Memory/Memory.h"
#include <vector>
#include <sstream>

namespace TEngine
{
	DebugUIRenderer::DebugUIRenderer()
		: font_(nullptr)
	{
	}

	void DebugUIRenderer::StartUp()
	{
		this->font_ = Font::GetDefaultFont();
		this->renderer_ = &Engine::Get().GetRenderer();

		vertex_shader_ = new DXVertexShader(*renderer_, L"TextVertexShader.cso");
		pixel_shader_ = new DXPixelShader(*renderer_, L"TextPixelShader.cso");
	}

	void DebugUIRenderer::VariableUpdate(F32 delta_time)
	{
		vertex_shader_->Bind();
		pixel_shader_->Bind();
		
		struct ConstBuff
		{
			Matrix4 projection;
		};
		
		ConstBuff cdata;
		cdata.projection = Matrix4::Orthographic(-1.f, 1.f, 0.0f, 1024.f, 0.0f, 768.f).Transpose();

		DXVSConstantBuffer<ConstBuff> cbuff(*renderer_, cdata);
		cbuff.Bind();

		F32 FPS = 1.f / delta_time;
		std::string title = "Odyssey Debug Build: " + std::to_string((int)FPS) + "FPS";

		RenderText(title, Vector2(0.f, 750.f), 1.f, Vector3(1.f, 1.f, 1.f));

		RenderText("MAIN HEAP:", Vector2(0.0f, 730.0f), 1.0f, Vector3::kOne);

		std::stringstream memstream;
		memstream << "Total Allocations: " << Memory::GetHeap().GetActiveCnt() 
			<< " Total Size: " << Memory::GetHeap().GetActiveSize();
		std::string memstr = memstream.str();

		RenderText(memstr, Vector2(0.0f, 710.0f), 1.f, Vector3::kOne);

		F32 distance = 20.f;
		for (int i = 0; i < Debug::screen_messages_.size(); i++)
		{
			RenderText(Debug::screen_messages_[i], 
				Vector2(0.f, 700.f - i * distance), 
				1.f, 
				Vector3(1.f, 1.f, 1.f));
		}
	}

	void DebugUIRenderer::FixedUpdate(F32 time_step)
	{
		// TODO: Some method of fixed update logging
	}

	void DebugUIRenderer::ShutDown()
	{
		this->font_ = nullptr;
		this->renderer_ = nullptr;
	}

	void DebugUIRenderer::RenderText(std::string text,
								const Vector2& pos,
								F32 scale,
								const Vector3& color)
	{
		F32 x = pos.x;
		F32 y = pos.y;

		// Render character by character
		std::string::const_iterator c;
		for (c = text.begin(); c != text.end(); c++)
		{
			Character font_char = font_->GetCharacter(*c);

			F32 xpos = x + font_char.bearing_.x * scale;
			F32 ypos = y - (font_char.size_.y - font_char.bearing_.y) * scale;
			F32 w = font_char.size_.x * scale;
			F32 h = font_char.size_.y * scale;

			Vertex vertices[6] = {
				{ Vector3(xpos, ypos + h, 0.f), Vector3(), Vector2(0.0, 0.0) },
				{ Vector3(xpos + w, ypos, 0.f), Vector3(), Vector2(1.0, 1.0) },
				{ Vector3(xpos, ypos, 0.f), Vector3(), Vector2(0.0, 1.0) },

				{ Vector3(xpos, ypos + h, 0.f), Vector3(), Vector2(0.0, 0.0) },
				{ Vector3(xpos + w, ypos + h, 0.f), Vector3(), Vector2(1.0, 0.0) },
				{ Vector3(xpos + w, ypos, 0.f), Vector3(), Vector2(1.0, 1.0) }
			};

			DXVertexBuffer vertex_buffer(Engine::Get().GetRenderer(), vertices, 6);
			vertex_buffer.Bind();

			font_char.dx_texture_->Bind();
			renderer_->Draw(6);

			// Advance is 1/64th of a pixel so multiply by 64
			x += (font_char.advance_ >> 6) * scale;
		}
	}
}
#endif
