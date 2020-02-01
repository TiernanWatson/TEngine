#include "Exception.h"
#include <sstream>

namespace TEngine
{
	Exception::Exception(const char* msg, const char* file, int line) noexcept
		: file(file), line(line), std::exception(msg)
	{
	}

	const char* Exception::DisplayString() const noexcept
	{
		std::stringstream result;
		result << GetType() << std::endl
			<< "File: " << file << std::endl
			<< "Line: " << line << std::endl
			<< what();
		displayString = result.str();

		return displayString.c_str();
	}

	const char* Exception::GetType() const noexcept
	{
		return "Exception";
	}
}
