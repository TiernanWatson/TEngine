#include "Keyboard.h"
#include "WinHeader.h"

namespace TEngine
{
	bool Keyboard::IsKeyPressed(unsigned char keyCode) const noexcept
	{
		return keyStates[keyCode];
	}

	void Keyboard::Clear() noexcept
	{
		keyStates.reset();
	}

	bool Keyboard::AutorepeatOn() const noexcept
	{
		return allowAutorepeat;
	}

	void Keyboard::SetAutorepeat(bool allow) noexcept
	{
		allowAutorepeat = allow;
	}

	void Keyboard::OnKeyPress(unsigned char keyCode) noexcept
	{
		keyStates[keyCode] = true;
		OutputDebugString("Key pressed\n");
	}

	void Keyboard::OnKeyRelease(unsigned char keyCode) noexcept
	{
		keyStates[keyCode] = false;
	}
}
