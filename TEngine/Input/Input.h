#pragma once
#include "../Core/PortableTypes.h"
#include "InputSystem.h"
#include "KeyCode.h"

namespace TEngine
{
	/**
	* Static class used to make input handling easy
	**/
	class Input
	{
	public:
		Input() = delete;

		static _FORCE_INLINE_ bool GetKey(KeyCode key) 
		{
			return input->GetKey(key);
		};

	private:
		static class InputSystem* input;
		friend class InputSystem;
	};
}
