#pragma once
#include "KeyCode.h"
#include "InputEvent.h"
#include <bitset>

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

		void StartUp();
		void Update();
		void ShutDown();

		bool GetKey(KeyCode key);

		void ReceiveEvent(InputEvent e);

	private:
		std::bitset<(size_t)KeyCode::Count> keyStates;
	};
}
