#include "StackAllocator.h"
#include <stdlib.h>
#include <iostream>
#include <string>

namespace TEngine
{
	StackAllocator::StackAllocator(const size stackSizeInBytes)
		: stackSizeInBytes(stackSizeInBytes)
	{
		topRawPtr = malloc(stackSizeInBytes);
		topPtr = reinterpret_cast<uintptr>(topRawPtr);
		std::cout << std::to_string(topPtr) << std::endl;
	}

	StackAllocator::~StackAllocator()
	{
		free(topRawPtr);
	}

	void* StackAllocator::Alloc(const size sizeInBytes)
	{
		void* location = reinterpret_cast<void*>(topPtr + currentMarker);

		currentMarker += sizeInBytes;

		return location;
	}

	void StackAllocator::FreeUpTo(const size marker)
	{
		currentMarker = marker;
	}

	void StackAllocator::Clear()
	{
		currentMarker = 0;
	}
}
