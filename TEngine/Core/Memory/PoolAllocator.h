#pragma once
#include "../PortableTypes.h"

namespace TEngine 
{
	/**
	* Pool of pre-defined size allocating fixed-size memory with no order restrictions
	**/
	class PoolAllocator
	{
	public:
		PoolAllocator() = delete;
		explicit PoolAllocator(size blockSize, size maxElements);
		~PoolAllocator();

	private:
		size blockSize;
		size maxElements;
		size currentCount = 0;
	};
}
