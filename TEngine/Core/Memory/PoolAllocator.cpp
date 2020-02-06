#include "PoolAllocator.h"
#include <stdlib.h>
#include <stdexcept>
#include <assert.h>

namespace TEngine
{
	PoolAllocator::PoolAllocator(USIZE blockSize, 
								USIZE maxElements,
								void* (*alloc)(USIZE))
		: block_size_(blockSize), max_elements_(maxElements)
	{
		assert(blockSize >= sizeof(Block));
		assert(maxElements >= 1);

		top_ = alloc(blockSize * maxElements);

		// Init all the blocks
		free_block_ = new (top_) Block{ nullptr };
		Block* currentBlock = free_block_;
		for (int i = 1; i < maxElements; i++) 
		{
			void* nextAddress = (void*)((UPTR)currentBlock + blockSize);
			Block* nextBlock = new (nextAddress) Block{ nullptr };
			currentBlock->next = nextBlock;
			currentBlock = nextBlock;
		}
	}

	PoolAllocator::~PoolAllocator()
	{
		free(top_);
	}

	void* PoolAllocator::Alloc()
	{
		if (free_block_ == nullptr)
			throw std::out_of_range("PoolAllocator::Alloc: No more free memory blocks kLeft.");

		void* alloc = free_block_;
		free_block_ = free_block_->next;

		return alloc;
	}

	void PoolAllocator::Free(void* address)
	{
		Block* newBlock = new (address) Block{ free_block_ };
		free_block_ = newBlock;
	}
}
