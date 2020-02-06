#pragma once
#include "WinHeader.h"
#include "../../Core/Exception.h"

#define HR_EXCEPT(hr) TEngine::HrException(hr, __FILE__, __LINE__)

// HRESULT hr_; must be declared before - otherwise hrcall would be called twice
#define THROW_IF_FAIL(hrcall) if (FAILED(hr = hrcall)) throw HR_EXCEPT(hr)

namespace TEngine
{
	class HrException : public Exception
	{
	public:
		HrException(HRESULT hr, const char* file, int line) noexcept;

		std::string TranslateHR() const noexcept;

		const char* GetType() const noexcept override
		{
			return "HRESULT Exception";
		}

		inline HRESULT GetHResult() const noexcept
		{
			return hr;
		}

	private:
		HRESULT hr;
	};
}