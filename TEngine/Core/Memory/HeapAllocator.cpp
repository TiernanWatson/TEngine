#include "HeapAllocator.h"
#include "../Exception.h"
#include "../../Helpers/Debug.h"

#define FULL_SIZE(heapHeader) kHeaderSize + heapHeader->payload_size

namespace TEngine
{
	HeapAllocator::HeapAllocator(USIZE size)
		: total_size_(size), expand_size_(1024 * 16)
	{
		assert(total_size_ > kMinBlockSize);

		data_ = malloc(size);

		if (data_ == NULL)
			throw EXCEPTION("malloc failed to allocate Heap memory!");

		first_block_ = (HeapHeader*)data_;
		first_block_->prev = nullptr;
		first_block_->next = nullptr;
		first_block_->payload_size = total_size_ - kHeaderSize;

		RBNode* free_root_ = (RBNode*)((UPTR*)first_block_ + 2);
		free_tree_ = new RBTree(free_root_);
	}

	HeapAllocator::~HeapAllocator()
	{
		free(data_);
		delete free_tree_;
	}

	void* HeapAllocator::Alloc(USIZE size)
	{
		RBNode* mem_block = free_tree_->Find(size);
		if (mem_block != nullptr)
		{
			// Move into payload since node overlaps head
			U8* result = (U8*)((USIZE*)mem_block + 1);
			USIZE remaining = mem_block->size - size;

			// Room to split a new block (could be async?)
			if (remaining >= kMinBlockSize)
			{
				USIZE new_size = remaining - kMinBlockSize;
				U8* new_location = result + size;
				RBNode* new_node = CreateNewBlock(new_location, new_size, nullptr, nullptr);
				free_tree_->Insert(new_node);
			}

#ifdef _DEBUG
			active_++;
			active_size_ += size;
#endif
			return (void*)result;
		}
		
		throw EXCEPTION("COULD NOT ALLOCATE MEMORY!");
	}

	void HeapAllocator::Free(void* pointer)
	{
		/*HeapHeader* header = (HeapHeader*)pointer - 1;
		header->is_free = true;

#ifdef _DEBUG
		active_--;
		active_size_ -= header->payload_size;
#endif
		// Merge adjacent blocks if they are free
		HeapHeader* next = header->next;
		HeapHeader* prev = header->prev;

		if (next != nullptr && next->is_free)
		{
			header->payload_size += FULL_SIZE(next);
			header->next = next->next;
		}

		if (prev != nullptr && prev->is_free)
		{
			prev->payload_size += FULL_SIZE(header);
			prev->next = next;
		}*/
	}

	RBNode* HeapAllocator::CreateNewBlock(void* location, USIZE size, HeapHeader* prev, HeapHeader* next)
	{
		HeapHeader* header = (HeapHeader*)location;
		header->prev = prev;
		header->next = next;
		header->payload_size = size;

		if (prev != nullptr)
			prev->next = header;

		RBNode* node = (RBNode*)((UPTR*)header + 2);
		return node;
	}
}
