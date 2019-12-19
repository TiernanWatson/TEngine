#pragma once
#include "../Core/PortableTypes.h"
#include "Metatype.h"
#include <vector>

namespace TEngine
{
	/**
	* A collection of component metatypes e.g. <position, velocity>
	**/
	struct Archetype
	{
		std::vector<Metatype> types;
		DataChunk* firstChunk;
	};
}
