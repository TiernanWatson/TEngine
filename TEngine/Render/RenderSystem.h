#pragma once
#include "../Core/PortableTypes.h"
#include "Shader/Shader.h"
#include "Texture/Texture.h"
#include "Models/Model.h"

struct GLFWwindow;

namespace TEngine
{
	class WorldSystem;
	class World;

	class RenderSystem
	{
	private:
		GLFWwindow* window;
		WorldSystem* worlds;
		World* world;

	public:
		RenderSystem();

		void StartUp(GLFWwindow* window, WorldSystem* worlds);
		void Update(float32 deltaTime);
		void ShutDown();
	};
}
