#pragma once
#include "../Core/PortableTypes.h"
#include "Archetype.h"

namespace TEngine
{
	constexpr USIZE kChunkDataSize = 16384;  // 16kB

	// A chunk of memory allocated to store a single archetype
	struct DataChunk
	{
		U8 data[kChunkDataSize];
		USIZE last_index = 0;
		Archetype* archetype = nullptr;
		DataChunk* next = nullptr;
	};
}
