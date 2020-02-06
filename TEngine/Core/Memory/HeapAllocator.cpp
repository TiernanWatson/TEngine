#include "HeapAllocator.h"

#define FULL_SIZE(heapHeader) kHeaderSize + heapHeader->size

namespace TEngine
{
	HeapAllocator::HeapAllocator(USIZE size)
		: total_size_(size), 
		data_(malloc(size)),
		first_block_((HeapHeader*)data_)
	{
		first_block_->prev = nullptr;
		first_block_->next = nullptr;
		first_block_->size = total_size_ - kHeaderSize;
		first_block_->is_free = true;
	}

	HeapAllocator::~HeapAllocator()
	{
		free(data_);
	}

	void* HeapAllocator::Alloc(USIZE size)
	{
		HeapHeader* header = first_block_;
		while (header != nullptr)
		{
			if (header->size >= size)
			{
				if (header->size - size > kHeaderSize)
				{
					USIZE advance = kHeaderSize + size;
					HeapHeader* newHeader = (HeapHeader*)((char*)header + advance);
					newHeader->prev = header;
					newHeader->next = header->next;
					newHeader->size = header->size - kHeaderSize - size;
					newHeader->is_free = true;
				}

#ifdef _DEBUG
				active_++;
				active_size_ += size;
#endif
				header->size = size;
				header->is_free = false;
				return (void*)(header + 1);
			}
			header = header->next;
		}

		return nullptr;
	}

	void HeapAllocator::Free(void* pointer)
	{
		HeapHeader* header = (HeapHeader*)pointer - 1;
		header->is_free = true;

#ifdef _DEBUG
		active_--;
		active_size_ -= header->size;
#endif

		// Merge adjacent blocks if they are free
		HeapHeader* next = header->next;
		HeapHeader* prev = header->prev;

		if (next != nullptr && next->is_free)
		{
			header->size += FULL_SIZE(next);
			header->next = next->next;
		}

		if (prev != nullptr && prev->is_free)
		{
			prev->size += FULL_SIZE(header);
			prev->next = next;
		}
	}
}
