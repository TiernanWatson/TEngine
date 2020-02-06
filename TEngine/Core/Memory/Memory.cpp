#include "Memory.h"
#include <assert.h>
#include <stdlib.h>

namespace TEngine
{
	void* Memory::Malloc(USIZE size, U8 alignment)
	{
		return malloc(size);
	}
}