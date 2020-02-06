#pragma once
#include "../Core/PortableTypes.h"
#include "Archetype.h"

namespace TEngine
{
	constexpr U32 kMem16kBytes = 16384;

	/**
	* A chunk of memory allocated to store a single archetype
	**/
	struct DataChunk
	{
		U8 data[kMem16kBytes];
		Archetype* archetype = nullptr;
		DataChunk* next = nullptr;
		USIZE last_index = 0;
	};
}
