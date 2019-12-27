#ifdef _DEBUG
#include "Debug.h"
#include "../Core/Math/Vector3.h"
#include <iostream>

namespace TEngine
{
	std::vector<std::string> Debug::screenMessages;

	void Debug::ScreenDebugText(std::string message)
	{
		screenMessages.push_back(message);
	}

	void Debug::LogDebugText(std::string message)
	{
		std::cout << message << "\n";
	}

	std::string Debug::Vec3ToStr(Vector3& v)
	{
		return "(" + std::to_string(v.x) 
			+ ", " + std::to_string(v.y) 
			+ ", " + std::to_string(v.z) + ")";
	}

	std::string Debug::PtrToStr(void* p)
	{
		return std::to_string(reinterpret_cast<uintptr>(p));
	}
}
#endif
