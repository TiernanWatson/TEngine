#pragma once
#include "../PortableTypes.h"
#include "HeapAllocator.h"

namespace TEngine
{
	class Memory
	{
	public:
		Memory() = delete;

		static void* Malloc(USIZE size, U8 alignment);

		static constexpr U8 kCacheLineSize = 64;

	private:
		static HeapAllocator heap_allocator_;
	};
}
