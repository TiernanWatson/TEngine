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
		if (unusedID.size() != 0)
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
		EntityDetails details = entityStorageMap[id];

		// TODO: Remove from datachunk

		unusedID.push(id);
		entityCount--;
	}

	Archetype* EntityManager::FindArchetype(Metatype* types, size count)
	{
		for (int i = 0; i < archetypes.size(); i++)
		{
			if (archetypes[i]->types.size() != count)
				continue;

			bool matches = true;
			for (int j = 0; j < archetypes[i]->types.size(); j++)
			{
				if (types[j].hash != archetypes[j]->types[j].hash)
				{
					matches = false;
					break;
				}
			}

			if (matches) return archetypes[i];
		}

		return nullptr;
	}

	Archetype* EntityManager::AddArchetype(Metatype* types, size count)
	{
		Archetype* a = new Archetype();

		for (size i = 0; i < count; i++)
			a->types.push_back(types[i]);

		a->firstChunk = new DataChunk();
		a->firstChunk->archetype = a;
		a->firstChunk->next = nullptr;

		archetypes.push_back(a);

		return a;
	}

	EntityManager& EntityManager::Main()
	{
		static EntityManager instance;
		return instance;
	}

	void* EntityManager::NewArchetypeInstance(Archetype* a, size& outChunk, size& outIndex)
	{
		uint8* start = a->firstChunk->data + a->firstChunk->lastIndex * a->width;

		uint8* p = start;
		for (int i = 0; i < a->types.size(); i++)
		{
			a->types[i].construct((void*)p);
			p += a->types[i].bytes;
		}

		outChunk = 0;
		outIndex = a->firstChunk->lastIndex;

		a->firstChunk->lastIndex++;

		return (void*)start;
	}
}
