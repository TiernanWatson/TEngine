#pragma once
#include "../PortableTypes.h"

namespace TEngine {
	class PoolAllocator
	{
	public:
		PoolAllocator() = delete;
		explicit PoolAllocator(size blockSize, size maxElements);
		~PoolAllocator();

	private:
		size blockSize;
		size maxElements;
		size currentCount;
	};
}
