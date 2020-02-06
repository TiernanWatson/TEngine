#ifdef _DEBUG
#include "Debug.h"
#include "../Platform/Windows/WinHeader.h"
#include "../Core/Math/Vector3.h"

namespace TEngine
{
	std::vector<std::string> Debug::screen_messages_;

	void Debug::ScreenDebugText(std::string message)
	{
		screen_messages_.push_back(message);
	}

	void Debug::LogDebugText(std::string message)
	{
		OutputDebugString((message + "\n").c_str());
	}

	std::string Debug::Vec3ToStr(Vector3& v)
	{
		return "(" + std::to_string(v.x) 
			+ ", " + std::to_string(v.y) 
			+ ", " + std::to_string(v.z) + ")";
	}

	std::string Debug::PtrToStr(void* p)
	{
		return std::to_string(reinterpret_cast<UPTR>(p));
	}
}
#endif
