#include "StackAllocator.h"
#include <stdlib.h>
#include <assert.h>
#include <iostream>
#include <string>

namespace TEngine
{
	StackAllocator::StackAllocator(USIZE size, void* (*alloc)(USIZE))
		: stack_size_(size), base_ptr_(alloc(size)), stack_pointer_(base_ptr_)
	{
	}

	StackAllocator::~StackAllocator()
	{
		free(base_ptr_);
	}

	void* StackAllocator::Alloc(USIZE size, U8 alignment)
	{
		assert((alignment & (alignment - 1)) == 0); // Should be power of 2

		UPTR testAddress = (UPTR)stack_pointer_;
		UPTR misalign = testAddress & (alignment - 1);
		PTRDIFF correction = alignment - misalign;

		correction = correction & (alignment - 1); // Stops skipping block if misalign = 0

		UPTR payload = testAddress + correction;

		UPTR newMarker = payload + size;

		if (newMarker > (UPTR)base_ptr_ + stack_size_)
			throw std::overflow_error("StackAllocator::Alloc not enough memory to allocate");

		stack_pointer_ = (void*)newMarker;
		
		return (void*)payload;
	}

	void StackAllocator::Free(void* ptr)
	{
		assert(ptr > base_ptr_ && ptr < stack_pointer_);

		stack_pointer_ = ptr;
	}

	void StackAllocator::Clear()
	{
		stack_pointer_ = nullptr;
	}
}
