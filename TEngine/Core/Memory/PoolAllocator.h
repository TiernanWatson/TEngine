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

		void* Alloc();
		void Free(void* address);

	private:
		struct Block {
			Block* next;
			Block(Block* next) : next(next) {}
		};

		size blockSize;
		size maxElements;

		void* top;
		Block* freeBlock;
	};
}
