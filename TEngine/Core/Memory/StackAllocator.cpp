#include "StackAllocator.h"
#include <stdlib.h>
#include <assert.h>
#include <iostream>
#include <string>

namespace TEngine
{
	StackAllocator::StackAllocator(maxint size, void* (*alloc)(maxint))
		: stackSize(size), basePtr(alloc(size)), stackPointer(basePtr)
	{
	}

	StackAllocator::~StackAllocator()
	{
		free(basePtr);
	}

	void* StackAllocator::Alloc(maxint size, uint8 alignment)
	{
		assert((alignment & (alignment - 1)) == 0); // Should be power of 2

		uintptr testAddress = (uintptr)stackPointer;
		uintptr misalign = testAddress & (alignment - 1);
		ptrdiff correction = alignment - misalign;

		correction = correction & (alignment - 1); // Stops skipping block if misalign = 0

		uintptr payload = testAddress + correction;

		uintptr newMarker = payload + size;

		if (newMarker > (uintptr)basePtr + stackSize)
			throw std::overflow_error("StackAllocator::Alloc not enough memory to allocate");

		stackPointer = (void*)newMarker;
		
		return (void*)payload;
	}

	void StackAllocator::Free(void* ptr)
	{
		assert(ptr > basePtr && ptr < stackPointer);

		stackPointer = ptr;
	}

	void StackAllocator::Clear()
	{
		stackPointer = nullptr;
	}
}
