#pragma once
#include "../PortableTypes.h"

namespace TEngine 
{
	/**
	* Stack of pre-defined size allocating blocks of various sized memory
	**/
	class StackAllocator
	{
	public:
		StackAllocator() = delete;
		explicit StackAllocator(size stackSizeInBytes);
		~StackAllocator();

		void* Alloc(size sizeInBytes, uint8 alignment);

		size GetMarker() const { return currentMarker; }

		void FreeUpTo(size marker);

		void Clear();

	private:
		// Maximum size of the stack
		size stackSizeInBytes;

		// Where the stack starts - doesn't change
		uintptr topPtr;

		// C style pointer used for clean up
		void* topRawPtr;

		// Relative to the stack, how many bytes in are we?
		size currentMarker = 0;
	};
}
