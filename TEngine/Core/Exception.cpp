#include "Exception.h"
#include <sstream>

namespace TEngine
{
	Exception::Exception(const char* msg, const char* file, int line) noexcept
		: file_(file), line_(line), std::exception(msg)
	{
	}

	const char* Exception::DisplayString() const noexcept
	{
		std::stringstream result;
		result << GetType() << std::endl
			<< "File: " << file_ << std::endl
			<< "Line: " << line_ << std::endl
			<< what();
		display_string_ = result.str();

		return display_string_.c_str();
	}

	const char* Exception::GetType() const noexcept
	{
		return "Exception";
	}
}
