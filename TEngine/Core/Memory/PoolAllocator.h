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
		explicit PoolAllocator(maxint blockSize, 
							maxint maxElements,
							void* (*alloc)(maxint) = malloc);
		PoolAllocator(const PoolAllocator&) = delete;
		PoolAllocator& operator=(const PoolAllocator&) = delete;
		~PoolAllocator();

		void* Alloc();
		void Free(void* address);

	private:
		struct Block {
			Block* next;
		};

		maxint blockSize;
		maxint maxElements;

		void* top;
		Block* freeBlock;
	};
}
