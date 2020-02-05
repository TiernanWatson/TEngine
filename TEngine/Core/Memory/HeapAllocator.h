#pragma once
#include "../PortableTypes.h"

namespace TEngine
{
	/*
	* Allocates a fixed-size of memory on the heap.
	* Returns arbitrarily-sized memory without context-switching
	*/
	class HeapAllocator
	{
	public:
		HeapAllocator(maxint size);
		HeapAllocator(const HeapAllocator&) = delete;
		HeapAllocator& operator=(const HeapAllocator&) = delete;
		~HeapAllocator();

		void* Alloc(maxint size);
		void Free(void* pointer);

#ifdef _DEBUG
		maxint GetActiveCnt() const 
		{
			return active;
		}

		maxint GetFreeCnt() const
		{
			return freed;
		}

		maxint GetActiveSize() const
		{
			return activeSize;
		}
#endif

	private:
		struct HeapHeader
		{
			HeapHeader* prev;
			HeapHeader* next;
			maxint size;  // Size of block excluding header
			bool isFree;
		};

		void* data;
		HeapHeader* firstBlock;
		maxint totalSize;

#ifdef _DEBUG
		maxint active = 0;
		maxint freed = 0;
		maxint activeSize = 0;
#endif

		static constexpr int32 HEADER_SIZE = sizeof(HeapHeader);
	};
}
