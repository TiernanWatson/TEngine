#pragma once
#include <exception>
#include <string>

namespace TEngine
{
	class Exception : public std::exception
	{
	public:
		Exception(const char* msg, const char* file, int line) noexcept;

		const char* DisplayString() const noexcept;
		virtual const char* GetType() const noexcept;

	protected:
		const char* file_;
		int line_;

		mutable std::string display_string_;  // Used so buffer isn't destroyed on GetWhat()
	};
}

#define EXCEPTION(msg) TEngine::Exception(msg, __FILE__, __LINE__)
