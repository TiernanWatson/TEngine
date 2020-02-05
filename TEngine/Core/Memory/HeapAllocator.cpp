#include "HeapAllocator.h"

#define FULL_SIZE(heapHeader) HEADER_SIZE + heapHeader->size

namespace TEngine
{
	HeapAllocator::HeapAllocator(maxint size)
		: totalSize(size), 
		data(malloc(size)),
		firstBlock((HeapHeader*)data)
	{
		firstBlock->prev = nullptr;
		firstBlock->next = nullptr;
		firstBlock->size = totalSize - HEADER_SIZE;
		firstBlock->isFree = true;
	}

	HeapAllocator::~HeapAllocator()
	{
		free(data);
	}

	void* HeapAllocator::Alloc(maxint size)
	{
		HeapHeader* header = firstBlock;
		while (header != nullptr)
		{
			if (header->size >= size)
			{
				if (header->size - size > HEADER_SIZE)
				{
					maxint advance = HEADER_SIZE + size;
					HeapHeader* newHeader = (HeapHeader*)((char*)header + advance);
					newHeader->prev = header;
					newHeader->next = header->next;
					newHeader->size = header->size - HEADER_SIZE - size;
					newHeader->isFree = true;
				}

#ifdef _DEBUG
				active++;
				activeSize += size;
#endif
				header->size = size;
				header->isFree = false;
				return (void*)(header + 1);
			}
			header = header->next;
		}

		return nullptr;
	}

	void HeapAllocator::Free(void* pointer)
	{
		HeapHeader* header = (HeapHeader*)pointer - 1;
		header->isFree = true;

#ifdef _DEBUG
		active--;
		activeSize -= header->size;
#endif

		// Merge adjacent blocks if they are free
		HeapHeader* next = header->next;
		HeapHeader* prev = header->prev;

		if (next != nullptr && next->isFree)
		{
			header->size += FULL_SIZE(next);
			header->next = next->next;
		}

		if (prev != nullptr && prev->isFree)
		{
			prev->size += FULL_SIZE(header);
			prev->next = next;
		}
	}
}
