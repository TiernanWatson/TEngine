#pragma once
#include "../Core/PortableTypes.h"

struct GLFWwindow;

namespace TEngine
{
	class WindowManager
	{
	public:
		WindowManager() = default;
		~WindowManager() = default;

		void StartUp();
		void Update(float32 deltaTime);
		void ShutDown();

		GLFWwindow* GetWindow() { return window; }

	private:
		GLFWwindow* window = nullptr;  // Game window pointer

		int16 width = 1920;
		int16 height = 1080;
		bool isFullscreen = false;
	};
}
