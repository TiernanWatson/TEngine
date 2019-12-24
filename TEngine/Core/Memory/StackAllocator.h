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
		explicit StackAllocator(maxint stackSizeInBytes);
		~StackAllocator();

		template<typename T, typename ...Args>
		T* NewOnStack(Args... args);

		void* Alloc(maxint sizeInBytes, uint8 alignment);

		maxint GetMarker() const { return currentMarker; }

		void FreeUpTo(maxint marker);

		void Clear();

	private:
		// Maximum maxint of the stack
		maxint stackSizeInBytes;

		// Where the stack starts - doesn't change
		uintptr topPtr;

		// C style pointer used for clean up
		void* topRawPtr;

		// Relative to the stack, how many size in are we?
		maxint currentMarker = 0;
	};

	template<typename T, typename ...Args>
	inline T* StackAllocator::NewOnStack(Args ...args)
	{
		void* p = Alloc(sizeof(T), alignof(T));

		return new (T) (args...);
	}
}
