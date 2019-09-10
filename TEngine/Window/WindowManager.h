#pragma once
#include "../Core/PortableTypes.h"

struct GLFWwindow;

namespace TEngine
{
	class WindowManager
	{
	private:
		GLFWwindow* window = nullptr;  // Game window pointer

		int16 width = 800;
		int16 height = 600;

	public:
		WindowManager() = default;
		WindowManager(int16 width, int16 height);
		~WindowManager() = default;

		void StartUp();
		void Update(float32 deltaTime);
		void ShutDown();

	public:
		//void framebufferSizeCallback(GLFWwindow* window, int width, int height);
	};
}
