#include "PoolAllocator.h"

TEngine::PoolAllocator::PoolAllocator(size blockSize, size maxElements)
	: blockSize(blockSize), maxElements(maxElements)
{

}

TEngine::PoolAllocator::~PoolAllocator()
{
}
