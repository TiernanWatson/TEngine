#include "EntityManager.h"
#include <assert.h>
#include "../Core/Memory/Memory.h"
#include "DataChunk.h"

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

	Archetype* EntityManager::FindArchetype(Metatype* types, maxint count) const
	{
		for (int i = 0; i < archetypes.size(); i++)
		{
			if (archetypes[i]->types.size() != count)
				continue;

			bool matches = true;
			for (int j = 0; j < archetypes[i]->types.size(); j++)
			{
				if (types[j].hash != archetypes[i]->types[j].hash)
				{
					matches = false;
					break;
				}
			}

			if (matches) return archetypes[i];
		}

		return nullptr;
	}

	Archetype* EntityManager::AddArchetype(Metatype* types, maxint count)
	{
		Archetype* a = new Archetype();

		maxint totalSize = 0;
		for (maxint i = 0; i < count; i++)
		{
			a->types.push_back(types[i]);
			totalSize += types[i].size;
		}

		void* alignedPointer = Memory::AlignedMalloc(sizeof(DataChunk), Memory::CACHE_LINE_SIZE);
		a->firstChunk = new (alignedPointer) DataChunk();
		a->firstChunk->archetype = a;
		a->firstChunk->next = nullptr;

		// First offset is always 0
		a->offsets.push_back(0);
		for (maxint i = 1; i < count; i++)
		{
			// Offset for i is determined by how much mem previous takes up
			// Amount of memory is proportional to the type size
			maxint offset = ((float32)types[i - 1].size / totalSize) * MEM_16K_BYTES;
			uint8 misalign = offset & (Memory::CACHE_LINE_SIZE - 1);

			a->offsets.push_back(offset - misalign);
		}

		archetypes.push_back(a);

		return a;
	}

	EntityManager& EntityManager::Main()
	{
		static EntityManager instance;
		return instance;
	}

	void EntityManager::NewArchetypeInstance(Archetype* a, maxint& outChunk, maxint& outIndex)
	{
		maxint index = a->firstChunk->lastIndex;
		uint8* start = a->firstChunk->data;

		// Loop all types and instantiate them at correct place (non-interleaved)
		for (int i = 0; i < a->types.size(); i++)
		{
			uint8* comp = start + a->offsets[i] + a->types[i].size * index;
			a->types[i].construct((void*)comp);
		}

		outChunk = 0;
		outIndex = index;

		a->firstChunk->lastIndex++;
	}
}
