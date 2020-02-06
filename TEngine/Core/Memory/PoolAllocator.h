#pragma once
#include "../PortableTypes.h"

namespace TEngine 
{
	/**
	* Pool of pre-defined USIZE allocating fixed-USIZE memory with no order restrictions
	**/
	class PoolAllocator
	{
	public:
		PoolAllocator() = delete;
		explicit PoolAllocator(USIZE block_size, 
							USIZE max_elements,
							void* (*alloc)(USIZE) = malloc);
		PoolAllocator(const PoolAllocator&) = delete;
		PoolAllocator& operator=(const PoolAllocator&) = delete;
		~PoolAllocator();

		void* Alloc();
		void Free(void* address);

	private:
		struct Block {
			Block* next;
		};

		USIZE block_size_;
		USIZE max_elements_;

		void* top_;
		Block* free_block_;
	};
}
