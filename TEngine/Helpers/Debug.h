#pragma once

#ifdef _DEBUG
#include <vector>
#include <string>

#define SCREEN_PRINT(message) TEngine::Debug::ScreenDebugText(message);
#define CONSOLE_PRINT(message) TEngine::Debug::LogDebugText(message);
#else
#define SCREEN_PRINT(message) 
#define CONSOLE_PRINT(message)
#endif

#ifdef _DEBUG
namespace TEngine
{
	class Vector3;

	/**
	* Class with only static members for debugging purposes
	* Not a namespace so message list is hidden and only accessed
	* by DebugUIRenderer friend class
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

		static std::string Vec3ToStr(Vector3& v);
		static std::string PtrToStr(void* p);

	private:
		static std::vector<std::string> screenMessages;

		static const int MAX_SCREEN_MSGS = 10;

		friend class DebugUIRenderer;
	};
}
#endif
