#pragma once
#include "KeyCode.h"

namespace TEngine
{
	enum class KeyEventType
	{
		Up,
		Down
	};

	// Describes key events such as up/down
	class InputEvent
	{
	public:
		InputEvent(KeyCode key, KeyEventType type);

		KeyCode GetKey() const;
		KeyEventType GetType() const;

	private:
		KeyCode key;
		KeyEventType type;
	};
}
