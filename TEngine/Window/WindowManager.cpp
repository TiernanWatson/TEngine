#include "WindowManager.h"
#include "../Game.h"
#include <iostream>
#include <assert.h>
#include <exception>
#include <glad/glad.h>
#include <glfw3.h>
#include "../Core/IO/FileSystem.h"

namespace TEngine
{
	void framebufferSizeCallback(GLFWwindow* window, int width, int height);

	WindowManager::WindowManager(int16 width, int16 height)
		: width(width), height(height)
	{
	}

	void WindowManager::StartUp()
	{
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		window = glfwCreateWindow(width, height, "T-Engine", nullptr, nullptr);
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

	void WindowManager::Update(float32 deltaTime)
	{
		if (glfwWindowShouldClose(window))
		{
			Game::Exit();
			return;
		}

		glfwSwapBuffers(window);
		glfwPollEvents();
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
