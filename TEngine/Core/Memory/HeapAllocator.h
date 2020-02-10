#pragma once
#include "../PortableTypes.h"
#include "RBTree.h"

namespace TEngine
{
	/*
	* Allocates a fixed-size_ of memory on the heap.
	* Returns arbitrarily-sized memory without context_-switching
	*/
	class HeapAllocator
	{
	public:
		HeapAllocator() = delete;
		HeapAllocator(USIZE size);
		HeapAllocator(const HeapAllocator&) = delete;
		HeapAllocator& operator=(const HeapAllocator&) = delete;
		~HeapAllocator();

		void* Alloc(USIZE size);
		void Free(void* pointer);

#ifdef _DEBUG
		USIZE GetActiveCnt() const 
		{
			return active_;
		}

		USIZE GetFreeCnt() const
		{
			return freed_;
		}

		USIZE GetActiveSize() const
		{
			return active_size_;
		}
#endif

	private:
		struct HeapHeader
		{
			HeapHeader* prev;
			HeapHeader* next;
			USIZE payload_size;
		};

#ifdef _DEBUG
		USIZE active_ = 0;
		USIZE freed_ = 0;
		USIZE active_size_ = 0;
#endif

		void* data_;
		HeapHeader* first_block_;
		RBTree* free_tree_;

		USIZE total_size_;
		USIZE expand_size_;

		RBNode* CreateNewBlock(void* location, USIZE size, HeapHeader* prev, HeapHeader* next);

		static constexpr U32 kHeaderSize = sizeof(HeapHeader);
		static constexpr U32 kNodeSize = sizeof(RBNode);
		static constexpr U32 kMinBlockSize = kHeaderSize + kNodeSize;
	};
}
