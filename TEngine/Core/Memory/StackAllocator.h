#pragma once
#include "../PortableTypes.h"

namespace TEngine 
{
	/**
	* Stack of fixed size allocating blocks of varying size memory
	**/
	class StackAllocator
	{
	public:
		StackAllocator() = delete;
		explicit StackAllocator(maxint size, void* (*alloc)(maxint) = malloc);
		StackAllocator(const StackAllocator&) = delete;
		StackAllocator& operator=(const StackAllocator&) = delete;
		~StackAllocator();

		template<typename T, typename ...Args>
		inline T* NewOnStack(Args... args);

		/*
		* Allocates 'size' bytes with specified alignment at top of stack
		*/
		void* Alloc(maxint size, uint8 alignment);

		/*
		* Frees down to (and including) ptr from the stack
		*/
		void Free(void* ptr);

		void Clear();

	private:
		maxint stackSize;
		void* basePtr;
		void* stackPointer;
	};

	template<typename T, typename ...Args>
	inline T* StackAllocator::NewOnStack(Args ...args)
	{
		void* p = Alloc(sizeof(T), alignof(T));
		return new (T) (args...);
	}
}
