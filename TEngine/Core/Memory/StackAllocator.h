#pragma once
#include "../PortableTypes.h"

namespace TEngine 
{
	/**
	* Stack of fixed size_ allocating blocks of varying size_ memory
	**/
	class StackAllocator
	{
	public:
		StackAllocator() = delete;
		explicit StackAllocator(USIZE size, void* (*alloc)(USIZE) = malloc);
		StackAllocator(const StackAllocator&) = delete;
		StackAllocator& operator=(const StackAllocator&) = delete;
		~StackAllocator();

		template<typename T, typename ...Args>
		inline T* NewOnStack(Args... args);

		/*
		* Allocates 'size_' bytes with specified alignment at top_ of stack
		*/
		void* Alloc(USIZE size, U8 alignment);

		/*
		* Frees kDown to (and including) ptr from the stack
		*/
		void Free(void* ptr);

		void Clear();

	private:
		USIZE stack_size_;
		void* base_ptr_;
		void* stack_pointer_;
	};

	template<typename T, typename ...Args>
	inline T* StackAllocator::NewOnStack(Args ...args)
	{
		void* p = Alloc(sizeof(T), alignof(T));
		return new (T) (args...);
	}
}
