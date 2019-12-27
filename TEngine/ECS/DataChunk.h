#pragma once
#include "../Core/PortableTypes.h"
#include "Archetype.h"

namespace TEngine
{
	constexpr uint32 MEM_16K_BYTES = 16384;

	/**
	* A chunk of memory allocated to store a single archetype
	**/
	struct DataChunk
	{
		uint8 data[MEM_16K_BYTES];
		Archetype* archetype = nullptr;
		DataChunk* next = nullptr;
		maxint lastIndex = 0;
	};
}
