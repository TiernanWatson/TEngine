#pragma once
#include "../PortableTypes.h"

namespace TEngine {
	class StackAllocator
	{
	public:
		typedef size Marker;

		StackAllocator() = delete;
		explicit StackAllocator(const size stackSizeInBytes);
		~StackAllocator();

		void* Alloc(const size sizeInBytes);

		Marker GetMarker() const { return currentMarker; }

		void FreeUpTo(const Marker marker);

		void Clear();

	private:
		// Maximum size of the stack
		size stackSizeInBytes;

		// Where the stack starts - doesn't change
		uPtr topPtr;

		// C style pointer used for clean up
		void* topRawPtr;

		// Relative to the stack, how many bytes in are we?
		Marker currentMarker = 0;
	};
}
