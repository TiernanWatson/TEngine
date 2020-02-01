#pragma once
#include "../../Core/PortableTypes.h"

namespace TEngine
{
	class Mouse
	{
	public:
		void OnLeftDown(int x, int y) noexcept;
		void OnLeftUp(int x, int y) noexcept;
		void OnRightDown(int x, int y) noexcept;
		void OnRightUp(int x, int y) noexcept;

		void OnMouseMove(int x, int y) noexcept;

	private:
		int x, y;

		bool isLeftPressed = false;
		bool isRightPressed = false;
	};
}
