#pragma once
#include "../Core/PortableTypes.h"
#include "Shader/Shader.h"
#include "Texture/Texture.h"
#include "Models/Model.h"

struct GLFWwindow;

namespace TEngine
{
	class RenderManager
	{
	private:
		GLFWwindow* window;
		Shader shader;
		Texture texture;
		Model model;

		void SetupVertexData();

	public:
		RenderManager();

		void StartUp(GLFWwindow* window);
		void Update(float32 deltaTime);
		void ShutDown();
	};
}
