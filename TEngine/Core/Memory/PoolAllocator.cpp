#include "PoolAllocator.h"
#include <stdlib.h>
#include <stdexcept>
#include <assert.h>

namespace TEngine
{
	PoolAllocator::PoolAllocator(maxint blockSize, 
								maxint maxElements,
								void* (*alloc)(maxint))
		: blockSize(blockSize), maxElements(maxElements)
	{
		assert(blockSize >= sizeof(Block));
		assert(maxElements >= 1);

		top = alloc(blockSize * maxElements);

		// Init all the blocks
		freeBlock = new (top) Block{ nullptr };
		Block* currentBlock = freeBlock;
		for (int i = 1; i < maxElements; i++) 
		{
			void* nextAddress = (void*)((uintptr)currentBlock + blockSize);
			Block* nextBlock = new (nextAddress) Block{ nullptr };
			currentBlock->next = nextBlock;
			currentBlock = nextBlock;
		}
	}

	PoolAllocator::~PoolAllocator()
	{
		free(top);
	}

	void* PoolAllocator::Alloc()
	{
		if (freeBlock == nullptr)
			throw std::out_of_range("PoolAllocator::Alloc: No more free memory blocks left.");

		void* alloc = freeBlock;
		freeBlock = freeBlock->next;

		return alloc;
	}

	void PoolAllocator::Free(void* address)
	{
		Block* newBlock = new (address) Block{ freeBlock };
		freeBlock = newBlock;
	}
}
