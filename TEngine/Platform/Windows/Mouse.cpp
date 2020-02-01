#include "Mouse.h"
#include "WinHeader.h"

namespace TEngine
{
	void Mouse::OnLeftDown(int x, int y) noexcept
	{
		isLeftPressed = true;
	}

	void Mouse::OnLeftUp(int x, int y) noexcept
	{
		isLeftPressed = false;
	}

	void Mouse::OnRightDown(int x, int y) noexcept
	{
		isRightPressed = true;
	}

	void Mouse::OnRightUp(int x, int y) noexcept
	{
		isRightPressed = false;
	}

	void Mouse::OnMouseMove(int x, int y) noexcept
	{
		this->x = x;
		this->y = y;
	}
}
