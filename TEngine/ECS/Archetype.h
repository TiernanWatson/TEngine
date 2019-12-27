#pragma once
#include "../Core/PortableTypes.h"
#include "Metatype.h"
#include <vector>
#include <set>

namespace TEngine
{
	/**
	* A collection of component metatypes e.g. <position, velocity>
	**/
	struct Archetype
	{
		std::set<maxint> hashes;
		std::vector<Metatype> types;
		std::vector<maxint> offsets;
		struct DataChunk* firstChunk;
	};
}
