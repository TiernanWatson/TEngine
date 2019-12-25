#pragma once
#include <vector>
#include <string>

#ifdef _DEBUG
#define SCREEN_PRINT(message) TEngine::Debug::ScreenDebugText(message);
#define CONSOLE_PRINT(message) TEngine::Debug::LogDebugText(message);
#else
#define SCREEN_PRINT(message) 
#define CONSOLE_PRINT(message)
#endif

namespace TEngine
{
	/**
	* Class with only static members for debugging purposes
	* Not a namespace so message list is hidden and only accessed
	* by DebugSystem friend class
	**/
	class Debug
	{
	public:
		Debug() = delete;

		/**
		* Displays a message on the in-game screen when in debug mode
		**/
		static void ScreenDebugText(std::string message);

		/**
		* Prints a debug message to the console
		**/
		static void LogDebugText(std::string message);

	private:
		static std::vector<std::string> screenMessages;

		friend class DebugSystem;
	};
}
