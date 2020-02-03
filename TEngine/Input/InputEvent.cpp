#include "InputEvent.h"

namespace TEngine
{
	InputEvent::InputEvent(KeyCode key, KeyEventType type)
		: key(key), type(type)
	{
	}

	KeyCode InputEvent::GetKey() const
	{
		return key;
	}

	KeyEventType InputEvent::GetType() const
	{
		return type;
	}
}
