#include "InputSystem.h"
#include <glfw3.h>
#include "Input.h"
#include <iostream>

namespace TEngine
{
	void InputSystem::StartUp(GLFWwindow* window)
	{
		this->window = window;

		Input::input = this;
	}

	void InputSystem::Update()
	{
		glfwPollEvents();
	}

	void InputSystem::ShutDown()
	{
		window = nullptr;

		Input::input = nullptr;
	}

	bool InputSystem::GetKey(KeyCode key)
	{
		return glfwGetKey(window, GetGlfwKey(key));
	}

	// Helper functions

	int InputSystem::GetGlfwKey(KeyCode key) const
	{
		switch (key)
		{
		case KeyCode::NONE:
			return GLFW_KEY_UNKNOWN;
		case KeyCode::SPACE:
			return GLFW_KEY_SPACE;
		case KeyCode::APOSTROPHE:
			return GLFW_KEY_APOSTROPHE;
		case KeyCode::COMMA:
		case KeyCode::MINUS:
		case KeyCode::PERIOD:
		case KeyCode::SLASH:
		case KeyCode::NUM0:
		case KeyCode::NUM1:
		case KeyCode::NUM2:
		case KeyCode::NUM3:
		case KeyCode::NUM4:
		case KeyCode::NUM5:
		case KeyCode::NUM6:
		case KeyCode::NUM7:
		case KeyCode::NUM8:
		case KeyCode::NUM9:
		case KeyCode::SEMICOLON:
		case KeyCode::EQUAL:
			return GLFW_KEY_COMMA - static_cast<int>(KeyCode::COMMA) +
				static_cast<int>(key);
		case KeyCode::A:
		case KeyCode::B:
		case KeyCode::C:
		case KeyCode::D:
		case KeyCode::E:
		case KeyCode::F:
		case KeyCode::G:
		case KeyCode::H:
		case KeyCode::I:
		case KeyCode::J:
		case KeyCode::K:
		case KeyCode::L:
		case KeyCode::M:
		case KeyCode::N:
		case KeyCode::O:
		case KeyCode::P:
		case KeyCode::Q:
		case KeyCode::R:
		case KeyCode::S:
		case KeyCode::T:
		case KeyCode::U:
		case KeyCode::V:
		case KeyCode::W:
		case KeyCode::X:
		case KeyCode::Y:
		case KeyCode::Z:
		case KeyCode::LEFT_BRACKET:
		case KeyCode::BACKSLASH:
		case KeyCode::RIGHT_BRACKET:
			return
				GLFW_KEY_A - static_cast<int>(KeyCode::A) + static_cast<int>(key);
		case KeyCode::GRAVE_ACCENT:
			return 96;
		case KeyCode::ESCAPE:
		case KeyCode::ENTER:
		case KeyCode::TAB:
		case KeyCode::BACKSPACE:
		case KeyCode::INSERT:
		case KeyCode::DEL:
		case KeyCode::RIGHT_ARROW:
		case KeyCode::LEFT_ARROW:
		case KeyCode::DOWN_ARROW:
		case KeyCode::UP_ARROW:
		case KeyCode::PAGE_UP:
		case KeyCode::PAGE_DOWN:
		case KeyCode::HOME:
		case KeyCode::END:
			return GLFW_KEY_ESCAPE - static_cast<int>(KeyCode::ESCAPE) +
				static_cast<int>(key);
		case KeyCode::CAPS_LOCK:
		case KeyCode::SCROLL_LOCK:
		case KeyCode::NUM_LOCK:
		case KeyCode::PRINT_SCREEN:
		case KeyCode::PAUSE:
			return GLFW_KEY_CAPS_LOCK - static_cast<int>(KeyCode::CAPS_LOCK) +
				static_cast<int>(key);
		case KeyCode::F1:
		case KeyCode::F2:
		case KeyCode::F3:
		case KeyCode::F4:
		case KeyCode::F5:
		case KeyCode::F6:
		case KeyCode::F7:
		case KeyCode::F8:
		case KeyCode::F9:
		case KeyCode::F10:
		case KeyCode::F11:
		case KeyCode::F12:
		case KeyCode::KP_0:
		case KeyCode::KP_1:
		case KeyCode::KP_2:
		case KeyCode::KP_3:
		case KeyCode::KP_4:
		case KeyCode::KP_5:
		case KeyCode::KP_6:
		case KeyCode::KP_7:
		case KeyCode::KP_8:
		case KeyCode::KP_9:
		case KeyCode::KP_DECIMAL:
		case KeyCode::KP_DIVIDE:
		case KeyCode::KP_MULTIPLY:
		case KeyCode::KP_SUBTRACT:
		case KeyCode::KP_ADD:
		case KeyCode::KP_ENTER:
		case KeyCode::KP_EQUAL:
			return GLFW_KEY_KP_0 - static_cast<int>(KeyCode::KP_0) +
				static_cast<int>(key);
		case KeyCode::LEFT_SHIFT:
		case KeyCode::LEFT_CONTROL:
		case KeyCode::LEFT_ALT:
		case KeyCode::LEFT_SUPER:
		case KeyCode::RIGHT_SHIFT:
		case KeyCode::RIGHT_CONTROL:
		case KeyCode::RIGHT_ALT:
		default:
			return GLFW_KEY_UNKNOWN;
		}
	}
}
