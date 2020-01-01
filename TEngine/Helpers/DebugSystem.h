#pragma once
#include "../Core/PortableTypes.h"
#include "../Core/Math/Vector3.h"
#include "../Core/Math/Vector2.h"
#include <string>

struct GLFWwindow;

namespace TEngine
{
	class Shader;
	class Vector3;
	class Vector2;
	class Font;

	class DebugSystem
	{
	public:
		DebugSystem();

		void StartUp(GLFWwindow* window);
		void VariableUpdate(float32 deltaTime);
		void FixedUpdate(float32 timeStep);
		void ShutDown();

	private:
		GLFWwindow* window;
		Font* font;
		uint32 shader;

		uint32 VAO, VBO;

		void RenderText(std::string text,
						const Vector2& pos,
						float32 scale,
						const Vector3& color);
	};
}
