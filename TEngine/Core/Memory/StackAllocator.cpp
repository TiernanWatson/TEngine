#include "StackAllocator.h"
#include <stdlib.h>
#include <assert.h>
#include <iostream>
#include <string>

namespace TEngine
{
	StackAllocator::StackAllocator(maxint stackSizeInBytes)
		: stackSizeInBytes(stackSizeInBytes)
	{
		topRawPtr = malloc(stackSizeInBytes);
		topPtr = reinterpret_cast<uintptr>(topRawPtr);
	}

	StackAllocator::~StackAllocator()
	{
		free(topRawPtr);
	}

	void* StackAllocator::Alloc(maxint sizeInBytes, uint8 alignment)
	{
		assert((alignment & (alignment - 1)) == 0);

		uintptr testAddress = topPtr + currentMarker;
		uintptr misalign = testAddress & (alignment - 1); // check for 1's to right of power of 2
		ptrdiff correction = alignment - misalign;

		correction = correction & (alignment - 1); // stops skipping block if misalign = 0

		maxint newMarker = currentMarker + correction + sizeInBytes;

		if (newMarker > topPtr + stackSizeInBytes)
			throw std::overflow_error("StackAllocator::Alloc not enough memory to allocate");

		currentMarker = newMarker;
		
		uintptr alignedAddress = testAddress + correction;
		return reinterpret_cast<void*>(alignedAddress);
	}

	void StackAllocator::FreeUpTo(maxint marker)
	{
		currentMarker = marker;
	}

	void StackAllocator::Clear()
	{
		currentMarker = 0;
	}
}
