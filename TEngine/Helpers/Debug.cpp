#include "Debug.h"
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
}
