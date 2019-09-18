#pragma once
#include "KeyCode.h"
#include <unordered_set>

struct GLFWwindow;

namespace TEngine
{
	/**
	* Main input manager responsible for events
	**/
	class InputSystem
	{
	public:
		InputSystem() = default;

		void StartUp(GLFWwindow* window);
		void Update();
		void ShutDown();

		bool GetKey(KeyCode key);

	private:
		GLFWwindow* window;

		int GetGlfwKey(KeyCode key) const;
	};
}
