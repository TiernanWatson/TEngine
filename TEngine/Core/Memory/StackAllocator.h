#pragma once
#include "../PortableTypes.h"

namespace TEngine 
{
	// Stack of fixed size allocating blocks of varying size
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

		// Allocates 'size' bytes with specified alignment at top of stack
		void* Alloc(USIZE size, U8 alignment);

		// Frees down to (and including) ptr from the stack
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
