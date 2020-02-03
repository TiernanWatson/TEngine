#include "Keyboard.h"
#include "WinHeader.h"
#include "../../Engine.h"

namespace TEngine
{
	bool Keyboard::AutorepeatOn() const noexcept
	{
		return allowAutorepeat;
	}

	void Keyboard::SetAutorepeat(bool allow) noexcept
	{
		allowAutorepeat = allow;
	}

	void Keyboard::OnKeyPress(unsigned char keyCode)
	{
		KeyCode key = WinKeyToCode(keyCode);
		Engine::Get().GetInputSys().ReceiveEvent(InputEvent(key, KeyEventType::Down));
	}

	void Keyboard::OnKeyRelease(unsigned char keyCode)
	{
		KeyCode key = WinKeyToCode(keyCode);
		Engine::Get().GetInputSys().ReceiveEvent(InputEvent(key, KeyEventType::Up));
	}

	KeyCode Keyboard::WinKeyToCode(unsigned char keyCode)
	{
		switch (keyCode)
		{
		case VK_TAB:
			return KeyCode::TAB;
		case VK_SPACE:
			return KeyCode::SPACE;
		case VK_RETURN:
			return KeyCode::ENTER;
		case VK_LSHIFT:
			return KeyCode::LEFT_SHIFT;
		case VK_RSHIFT:
			return KeyCode::RIGHT_SHIFT;
		case VK_LCONTROL:
			return KeyCode::LEFT_CONTROL;
		case VK_RCONTROL:
			return KeyCode::RIGHT_CONTROL;
		// ASCII Key characters (no windows neumonic available)
		case 0x30:
			return KeyCode::NUM0;
		case 0x31:
			return KeyCode::NUM1;
		case 0x32:
			return KeyCode::NUM2;
		case 0x33:
			return KeyCode::NUM3;
		case 0x34:
			return KeyCode::NUM4;
		case 0x35:
			return KeyCode::NUM5;
		case 0x36:
			return KeyCode::NUM6;
		case 0x37:
			return KeyCode::NUM7;
		case 0x38:
			return KeyCode::NUM8;
		case 0x39:
			return KeyCode::NUM9;
		case 0x41:
			return KeyCode::A;
		case 0x42:
			return KeyCode::B;
		case 0x43:
			return KeyCode::C;
		case 0x44:
			return KeyCode::D;
		case 0x45:
			return KeyCode::E;
		case 0x46:
			return KeyCode::F;
		case 0x47:
			return KeyCode::G;
		case 0x48:
			return KeyCode::H;
		case 0x49:
			return KeyCode::I;
		case 0x4A:
			return KeyCode::J;
		case 0x4B:
			return KeyCode::K;
		case 0x4C:
			return KeyCode::L;
		case 0x4D:
			return KeyCode::M;
		case 0x4E:
			return KeyCode::N;
		case 0x4F:
			return KeyCode::O;
		case 0x50:
			return KeyCode::P;
		case 0x51:
			return KeyCode::Q;
		case 0x52:
			return KeyCode::R;
		case 0x53:
			return KeyCode::S;
		case 0x54:
			return KeyCode::T;
		case 0x55:
			return KeyCode::U;
		case 0x56:
			return KeyCode::V;
		case 0x57:
			return KeyCode::W;
		case 0x58:
			return KeyCode::X;
		case 0x59:
			return KeyCode::Y;
		case 0x5A:
			return KeyCode::Z;
		default:
#ifdef _DEBUG
			throw EXCEPTION("Unidentified WinKey!");
#else
			return KeyCode::NONE;
#endif
		}
	}
}
