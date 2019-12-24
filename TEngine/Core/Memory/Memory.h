#pragma once
#include "../PortableTypes.h"

namespace TEngine
{
	class StackAllocator;

	namespace Memory
	{
		constexpr uint8 CACHE_LINE_SIZE = 64;

		/**
		* Allocates size at a certain alignment using standard malloc
		**/
		void* AlignedMalloc(maxint bytes, uint8 alignment);

		/**
		* Deallocates memory that was allocated using AlignedMalloc
		**/
		void AlignedFree(void* address);
	}
}
