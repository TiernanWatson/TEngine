#include "Entity.h"

namespace TEngine
{
	uint32 Entity::currentId = 0;

	Entity::Entity() : id(currentId + 1)
	{
		currentId++;
	}
}
