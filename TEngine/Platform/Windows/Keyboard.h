#pragma once
#include "WinHeader.h"
#include "../../Input/KeyCode.h"

namespace TEngine
{
	class Keyboard
	{
	public:
		bool AutorepeatOn() const noexcept;
		void SetAutorepeat(bool allow) noexcept;

	private:
		// Used by WindowsOS to set key states
		void OnKeyPress(unsigned char keyCode);
		void OnKeyRelease(unsigned char keyCode);

		KeyCode WinKeyToCode(unsigned char keyCode);

		bool allowAutorepeat = false;
		
		friend class WindowsOS;
	};
}
