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
		void OnKeyPress(unsigned char key_code);
		void OnKeyRelease(unsigned char key_code);

		KeyCode WinKeyToCode(unsigned char key_code);

		bool allow_autorepeat_ = false;
		
		friend class WindowsOS;
	};
}
