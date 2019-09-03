#include "PoolAllocator.h"

namespace TEngine
{
	PoolAllocator::PoolAllocator(size blockSize, size maxElements)
		: blockSize(blockSize), maxElements(maxElements)
	{

	}

	PoolAllocator::~PoolAllocator()
	{
	}
}
