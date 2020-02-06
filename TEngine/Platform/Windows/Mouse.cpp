#include "Mouse.h"
#include "WinHeader.h"

namespace TEngine
{
	void Mouse::OnLeftDown(int x, int y) noexcept
	{
		is_left_pressed_ = true;
	}

	void Mouse::OnLeftUp(int x, int y) noexcept
	{
		is_left_pressed_ = false;
	}

	void Mouse::OnRightDown(int x, int y) noexcept
	{
		is_right_pressed_ = true;
	}

	void Mouse::OnRightUp(int x, int y) noexcept
	{
		is_right_pressed_ = false;
	}

	void Mouse::OnMouseMove(int x, int y) noexcept
	{
		this->x = x;
		this->y = y;
	}
}
