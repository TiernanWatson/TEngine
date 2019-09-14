#include "Memory.h"
#include <assert.h>
#include <stdlib.h>

namespace TEngine
{
	void* Memory::AlignedAlloc(size bytes, uint8 alignment)
	{
		assert(alignment >= 8 && alignment <= 128);
		assert((alignment & (alignment - 1)) == 0); // power of 2

		size totalSize = bytes + alignment;
		
		uintptr rawAddress = reinterpret_cast<uintptr>(malloc(totalSize));

		uint8 mask = (alignment - 1);
		uintptr misalignment = (rawAddress & mask);
		ptrdiff adjustment = alignment - misalignment;

		// Don't consider case where adjustment == alignment, need that space
		uintptr alignedAddress = rawAddress + adjustment;

		// Store metadata for freeing memory
		reinterpret_cast<uint8*>(alignedAddress)[-1] = (uint8)adjustment;

		return reinterpret_cast<void*>(alignedAddress);
	}

	void Memory::AlignedFree(void* address)
	{
		uint8* bytePtr = reinterpret_cast<uint8*>(address);
		ptrdiff adjustment = bytePtr[-1]; // Get the stored adjustment

		uintptr alignedAddress = reinterpret_cast<uintptr>(address);
		uintptr rawAddress = alignedAddress - adjustment; 

		void* toFree = reinterpret_cast<void*>(rawAddress);

		free(toFree);
	}
}