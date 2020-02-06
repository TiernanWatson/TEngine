#pragma once
#include "../../Platform/Windows/WinHeader.h"
#include "../../Core/Exception.h"
#include "DXInfoManager.h"

#define DEVICE_REMOVED_EXCEPT(reason, hr) TEngine::DeviceRemovedException(reason, hr, __FILE__, __LINE__);
#define HR_D3D11_EXCEPT(hr) TEngine::HrD3D11Exception(hr, __FILE__, __LINE__)
#define D3D11_EXCEPT(msg) TEngine::D3D11Exception(msg, __FILE__, __LINE__)

// HRESULT hr_; must be declared before - otherwise hrcall would be called twice
#define THROW_IF_FAIL(hrcall) if (FAILED(hr = hrcall)) throw HR_D3D11_EXCEPT(hr)

namespace TEngine
{
	class D3D11Exception : public Exception
	{
	public:
		D3D11Exception(const char* msg, const char* file, int line) noexcept;

		const char* GetType() const noexcept override
		{
			return "D3D11 Exception";
		}
	};

	class HrD3D11Exception : public D3D11Exception
	{
	public:
		HrD3D11Exception(HRESULT hr, const char* file, int line) noexcept;

		const char* GetType() const noexcept override
		{
			return "D3D11 HRESULT Exception";
		}

		inline HRESULT GetHResult() const noexcept
		{
			return hr_;
		}

	private:
		HRESULT hr_;
	};

	class DeviceRemovedException : public HrD3D11Exception
	{
	public:
		DeviceRemovedException(HRESULT reason, HRESULT hr, const char* file, int line) noexcept;

		const char* GetType() const noexcept override
		{
			return "Device Removed Exception";
		}

		inline HRESULT GetReason()
		{
			return reason_;
		}

	private:
		HRESULT reason_;
	};
}