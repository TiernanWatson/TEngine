#include "WindowManager.h"
#include <glad/glad.h>
#include <glfw3.h>
#include "../Core/IO/FileSystem.h"
#include "../Core/Config/Config.h"
#include "../Core/Config/ConfigVar.h"

namespace TEngine
{
	// Must declare this here because of type_ error if under TEngine::
	void framebufferSizeCallback(GLFWwindow* window, int width, int height);

	void WindowManager::StartUp()
	{
		ConfigVar titleVar = CONFIG_VAL("Window", "title", ConfigVar("Odyssey"));
		ConfigVar widthVar = CONFIG_VAL("Window", "width_", ConfigVar("800"));
		ConfigVar heightVar = CONFIG_VAL("Window", "height_", ConfigVar("600"));
		ConfigVar fullscreenVar = CONFIG_VAL("Window", "is_fullscreen_", ConfigVar("false"));

		width = widthVar.GetInt();
		height = heightVar.GetInt();
		isFullscreen = fullscreenVar.GetBool();

		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		window = glfwCreateWindow(
			width, 
			height, 
			titleVar.GetValue().c_str(), 
			isFullscreen ? glfwGetPrimaryMonitor() : nullptr, 
			nullptr
		);

		if (!window)
		{
			throw std::exception("WindowManager::StartUp: Could not create GLFW window.");
		}

		glfwMakeContextCurrent(window);
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			throw std::exception("WindowManager::StartUp: Could not load glad");
		}

		glViewport(0, 0, width, height);

		glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
	}

	void WindowManager::Update(F32 deltaTime)
	{
		if (glfwWindowShouldClose(window))
		{
			//Game::Exit();
			return;
		}

		glfwSwapBuffers(window);
	}

	void WindowManager::ShutDown()
	{
		glfwDestroyWindow(window);
		window = nullptr;
		glfwTerminate();
	}

	void framebufferSizeCallback(GLFWwindow* window, int width, int height)
	{
		glViewport(0, 0, width, height);
	}
}
