#include "DebugSystem.h"
#include "Debug.h"
#include "../Core/Math/Matrix4.h"
#include "../Core/IO/FileSystem.h"
#include "../Render/Shader/Shader.h"
#include "../Render/UI/Character.h"
#include "../Render/UI/Font.h"
#include <glad/glad.h>
#include <glfw3.h>
#include <vector>
#include <iostream>

namespace TEngine
{
	DebugSystem::DebugSystem()
		: window(nullptr), 
		font(nullptr), 
		shader(nullptr)
	{
	}

	void DebugSystem::StartUp(GLFWwindow* window)
	{
		this->window = window;
		this->font = Font::GetDefaultFont();

		const char* vertSource = FileSystem::Instance().ReadString(
			"D:\\TEngine\\TEngine\\Resources\\Shaders\\Vertex\\uitext.vert");

		const char* fragSource = FileSystem::Instance().ReadString(
			"D:\\TEngine\\TEngine\\Resources\\Shaders\\Fragment\\uitext.frag");

		this->shader = new Shader(vertSource, fragSource);

		delete vertSource, fragSource;

		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);

		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float32) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float32), 0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

	void DebugSystem::VariableUpdate(float32 deltaTime)
	{
		Matrix4 proj = Matrix4::Orthographic(-1.f, 1.f, 0.0f, 1280.f, 0.0f, 720.f);
		shader->Use();
		shader->SetMat4("projection", proj.Transpose());

		float32 FPS = 1.f / deltaTime;
		std::string title = "Odyssey Game Engine Debug Build: " + std::to_string((int)FPS) + "FPS";

		RenderText(title, Vector2(5.f, 700.f), 1.f, Vector3(1.f, 1.f, 1.f));

		for (const std::string& s : Debug::screenMessages)
			RenderText(s, Vector2(5.0f, 680.0f), 1.f, Vector3(1.f, 1.f, 1.f));

		// Don't want to repeat messages
		Debug::screenMessages.clear();
	}

	void DebugSystem::FixedUpdate(float32 timeStep)
	{
		// TODO: Some method of fixed update logging
	}

	void DebugSystem::ShutDown()
	{
		this->window = nullptr;
		this->font = nullptr;
		this->shader = nullptr;
	}

	void DebugSystem::RenderText(std::string text,
								const Vector2& pos,
								float32 scale,
								const Vector3& color)
	{
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

		glUniform3f(glGetUniformLocation(shader->shaderProgram, "textColor"), color.x, color.y, color.z);
		glActiveTexture(GL_TEXTURE0);
		glBindVertexArray(VAO);

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

			float32 vertices[6][4] = {
				{ xpos,     ypos + h,   0.0, 0.0 },
				{ xpos,     ypos,       0.0, 1.0 },
				{ xpos + w, ypos,       1.0, 1.0 },

				{ xpos,     ypos + h,   0.0, 0.0 },
				{ xpos + w, ypos,       1.0, 1.0 },
				{ xpos + w, ypos + h,   1.0, 0.0 }
			};

			glBindTexture(GL_TEXTURE_2D, fontChar.textureID);

			glBindBuffer(GL_ARRAY_BUFFER, VBO);
			glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
			glBindBuffer(GL_ARRAY_BUFFER, 0);

			glDrawArrays(GL_TRIANGLES, 0, 6);

			// Advance is 1/64th of a pixel so multiply by 64
			x += (fontChar.advance >> 6) * scale;
		}

		glBindVertexArray(0);
		glBindTexture(GL_TEXTURE_2D, 0);

		glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	}
}
