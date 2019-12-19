#include "EntityManager.h"
#include <assert.h>
#include <iostream>

namespace TEngine
{
	EntityManager::EntityManager()
	{
		
	}

	uint32 EntityManager::NewEntity()
	{
		uint32 id;
		if (unusedID.size != 0)
		{
			id = unusedID.front();
			unusedID.pop();
		}
		else 
		{
			id = entityCount;
		}

		entityCount++;
		return id;
	}

	void EntityManager::DeleteEntity(uint32 id)
	{
		unusedID.push(id);
		entityCount--;
	}

	Archetype* EntityManager::FindArchetype(Metatype** types, size count)
	{
		for (int i = 0; i < archetypes.size; i++)
		{
			if (archetypes[i].types.size != count)
				continue;

			bool matches = true;
			for (int j = 0; j < archetypes[i].types.size(); j++)
			{
				if (types[j]->hash != archetypes[j].types[j].hash)
				{
					matches = false;
					break;
				}
			}

			if (matches) return &archetypes[i];
		}

		return nullptr;
	}

	EntityManager& EntityManager::Main()
	{
		static EntityManager instance;
		return instance;
	}
}
