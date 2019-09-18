#pragma once
#include "../Core/PortableTypes.h"
#include "KeyCode.h"

namespace TEngine
{
	/**
	* Static class used to make input handling easy
	**/
	class Input
	{
	public:
		static _FORCE_INLINE_ bool GetKey(KeyCode key);

		static class InputSystem* GetSystem() { return input; }

	private:
		Input();

		static class InputSystem* input;
		friend class InputSystem;
	};
}
