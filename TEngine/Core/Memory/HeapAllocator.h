#pragma once
#include "../PortableTypes.h"

namespace TEngine
{
	struct AllocHeader
	{
		// Lowest bit 1 if allocated
		USIZE size;
	};

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
			USIZE size;  // Size of block excluding header
			bool is_free;
		};

		void* data_;
		HeapHeader* first_block_;
		USIZE total_size_;
		U32 expand_size_;  // TODO: EXPANSION

#ifdef _DEBUG
		USIZE active_ = 0;
		USIZE freed_ = 0;
		USIZE active_size_ = 0;
#endif

		static constexpr I32 kHeaderSize = sizeof(HeapHeader);
	};
}
