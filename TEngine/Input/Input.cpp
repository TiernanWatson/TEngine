#include "Input.h"
#include <glfw3.h>
#include "InputSystem.h"

namespace TEngine
{
	InputSystem* Input::input = nullptr;

	bool Input::GetKey(KeyCode key)
	{
		return input->GetKey(key);
	}
}