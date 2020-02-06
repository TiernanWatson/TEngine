#pragma once
#include "../Core/PortableTypes.h"
#include <Windows.h>

struct GLFWwindow;

namespace TEngine
{
	class WindowManager
	{
	public:
		WindowManager() = default;
		~WindowManager() = default;

		void StartUp();
		void Update(F32 deltaTime);
		void ShutDown();

		GLFWwindow* GetWindow() { return window; }

	private:
		GLFWwindow* window = nullptr;  // Game window pointer

		I16 width = 1920;
		I16 height = 1080;
		bool isFullscreen = false;
	};
}
