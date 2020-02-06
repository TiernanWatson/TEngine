#pragma once
#include "../Core/PortableTypes.h"
#include "Metatype.h"
#include <vector>
#include <set>

namespace TEngine
{
	struct DataChunk;

	/**
	* A collection of component metatypes e.g. <position, velocity>
	**/
	struct Archetype
	{
		std::set<USIZE> hashes;
		std::vector<Metatype> types;
		std::vector<USIZE> offsets;
		DataChunk* first_chunk;
		U16 total_size;
	};
}
