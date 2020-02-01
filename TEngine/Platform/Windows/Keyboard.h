#pragma once
#include "../../Core/PortableTypes.h"
#include <bitset>

namespace TEngine
{
	class Keyboard
	{
	public:
		bool IsKeyPressed(unsigned char keyCode) const noexcept;
		void Clear() noexcept;

		bool AutorepeatOn() const noexcept;
		void SetAutorepeat(bool allow) noexcept;

	private:
		// Used by WindowsOS to set key states
		void OnKeyPress(unsigned char keyCode) noexcept;
		void OnKeyRelease(unsigned char keyCode) noexcept;

		static constexpr uint32 NUM_KEYS = 256u;
		std::bitset<NUM_KEYS> keyStates;

		bool allowAutorepeat = false;
		
		friend class WindowsOS;
	};
}
