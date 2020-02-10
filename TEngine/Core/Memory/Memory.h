#pragma once
#include "../PortableTypes.h"
#include "HeapAllocator.h"

namespace TEngine
{
	class Memory
	{
	public:
		static constexpr U8 kCacheLineSize = 64;

		Memory() = delete;  // Static class

		static void* Malloc(USIZE size);
		static void Free(void* ptr);

		static inline HeapAllocator& GetHeap()
		{
			return heap_allocator_;
		}

	private:
		static HeapAllocator heap_allocator_;
	};
}

#define memalloc(size) Memory::Malloc(size)
#define memfree(ptr) Memory::Free(ptr)
