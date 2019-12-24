#pragma once
#include "../PortableTypes.h"

namespace TEngine 
{
	/**
	* Pool of pre-defined maxint allocating fixed-maxint memory with no order restrictions
	**/
	class PoolAllocator
	{
	public:
		PoolAllocator() = delete;
		explicit PoolAllocator(maxint blockSize, maxint maxElements);
		~PoolAllocator();

		void* Alloc();
		void Free(void* address);

	private:
		struct Block {
			Block* next;
			Block(Block* next) : next(next) {}
		};

		maxint blockSize;
		maxint maxElements;

		void* top;
		Block* freeBlock;
	};
}
