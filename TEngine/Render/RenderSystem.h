#pragma once
#include "../Core/PortableTypes.h"
#include "Shader/Shader.h"
#include "Texture/Texture.h"
#include "Models/Model.h"

struct GLFWwindow;

namespace TEngine
{
	class RenderSystem
	{
	private:
		GLFWwindow* window;
		Shader shader;
		Texture texture;
		Model model;

		void SetupVertexData();

		void SetupMesh(const Mesh& mesh, uint32& VAO, uint32& VBO, uint32& EBO);

	public:
		RenderSystem();

		void StartUp(GLFWwindow* window);
		void Update(float32 deltaTime);
		void ShutDown();
	};
}
