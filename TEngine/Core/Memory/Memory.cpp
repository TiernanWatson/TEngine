#include "Memory.h"
#include <assert.h>
#include <stdlib.h>
#include "../../Helpers/Debug.h"

namespace TEngine
{
	constexpr USIZE kHeapDefaultSize = 1024 * 1024; 

	HeapAllocator Memory::heap_allocator_(kHeapDefaultSize);

	void* Memory::Malloc(USIZE size)
	{
		assert(size >= 1 && "Tried to malloc < 1");

		return heap_allocator_.Alloc(size);
	}

	void Memory::Free(void* ptr)
	{
		heap_allocator_.Free(ptr);
	}
}