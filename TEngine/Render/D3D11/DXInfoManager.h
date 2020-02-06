#pragma once
#include "../../Platform/Windows/WinHeader.h"
#include <vector>
#include <string>
#include <dxgidebug.h>
#include <wrl.h>

namespace TEngine
{
	class DXInfoManager
	{
	public:
		DXInfoManager();
		~DXInfoManager() = default;
		DXInfoManager(const DXInfoManager&) = delete;
		DXInfoManager& operator=(const DXInfoManager&) = delete;

		void Mark();
		std::vector<std::string> GetMessage();

	private:
		unsigned long long mark_ = 0;
		Microsoft::WRL::ComPtr<IDXGIInfoQueue> info_queue_;
	};
}
