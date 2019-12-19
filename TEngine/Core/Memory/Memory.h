#pragma once
#include "../PortableTypes.h"

namespace TEngine
{
	class Memory
	{
	private:
		Memory(); // static class

	public:
		/**
		* Allocates bytes at a certain alignment using standard malloc
		**/
		static void* AlignedMalloc(size bytes, uint8 alignment);

		/**
		* Deallocates memory that was allocated using AlignedMalloc
		**/
		static void AlignedFree(void* address);
	};
}
