#pragma once
#include "../Core/PortableTypes.h"

struct GLFWwindow;

namespace TEngine
{
	class WindowManager
	{
	private:
		GLFWwindow* window = nullptr;  // Game window pointer

		int16 width = 1280;
		int16 height = 720;

	public:
		WindowManager() = default;
		WindowManager(int16 width, int16 height);
		~WindowManager() = default;

		void StartUp();
		void Update(float32 deltaTime);
		void ShutDown();

		GLFWwindow* GetWindow() { return window; }
	};
}
