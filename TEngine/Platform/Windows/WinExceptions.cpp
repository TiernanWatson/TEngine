#include "WinExceptions.h"
#include <comdef.h>

namespace TEngine
{
	HrException::HrException(HRESULT hr, const char* file, int line) noexcept
		: hr(hr), Exception(TranslateHR().c_str(), file, line)
	{
		
	}

	std::string HrException::TranslateHR() const noexcept
	{
		_com_error err(hr);

		return err.ErrorMessage();
	}
}
