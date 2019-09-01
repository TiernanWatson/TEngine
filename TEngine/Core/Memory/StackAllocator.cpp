#include "StackAllocator.h"
#include <stdlib.h>
#include <iostream>
#include <string>


TEngine::StackAllocator::StackAllocator(const size stackSizeInBytes)
	: stackSizeInBytes(stackSizeInBytes) 
{
	topRawPtr = malloc(stackSizeInBytes);
	topPtr = reinterpret_cast<uPtr>(topRawPtr);
	std::cout << std::to_string(topPtr) << std::endl;
}

TEngine::StackAllocator::~StackAllocator()
{
	free(topRawPtr);
}

void* TEngine::StackAllocator::Alloc(const size sizeInBytes)
{
	void* location = reinterpret_cast<void*>(topPtr + currentMarker);

	currentMarker += sizeInBytes;

	return location;
}

void TEngine::StackAllocator::FreeUpTo(const Marker marker)
{
	currentMarker = marker;
}

void TEngine::StackAllocator::Clear()
{
	currentMarker = 0;
}
