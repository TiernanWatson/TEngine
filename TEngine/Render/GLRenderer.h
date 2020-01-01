#pragma once
#include "../Core/PortableTypes.h"
#include "GLTextureInfo.h"
#include "GLMeshInstance.h"
#include <unordered_map>

struct GLFWwindow;

namespace TEngine
{
	class WorldSystem;
	class World;
	class Mesh;
	class Matrix4;

	/**
	* Class responsible for updating visuals when using OpenGL
	**/
	class GLRenderer
	{
	public:
		GLRenderer();

		void StartUp(GLFWwindow* window, WorldSystem* worlds);
		void Render(float32 deltaTime);
		void ShutDown();

	private:
		GLFWwindow* window;
		WorldSystem* worlds;
		World* world;

		// Allows multiple components to share VAOs without slowing down performance
		std::unordered_map<Mesh*, GLMeshInstance*> meshInstances;
	};
}
