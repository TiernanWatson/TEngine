#include "EntityManager.h"
#include <assert.h>
#include "../Core/Memory/Memory.h"
#include "DataChunk.h"

namespace TEngine
{
	EntityManager::EntityManager()
	{
	}

	EntityManager::~EntityManager()
	{
		for (Archetype* a : archetypes) 
			delete a;
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

	std::vector<Archetype*> EntityManager::MatchingArchetypes(Metatype* inc, maxint count) const
	{
		std::vector<Archetype*> result;
		for (maxint i = 0; i < archetypes.size(); i++)
		{
			bool matches = true;
			for (maxint j = 0; j < count; j++)
			{
				if (archetypes[i]->hashes.find(inc[j].hash) ==
					archetypes[i]->hashes.end())
				{
					matches = false;
					break;
				}
			}

			if (matches)
				result.push_back(archetypes[i]);
		}

		return result;
	}

	Archetype* EntityManager::AddArchetype(Metatype* types, maxint count)
	{
		assert(count != 0);

		Archetype* a = new Archetype();

		// First offset is always 0, so this is outside of loop 
		a->offsets.push_back(0);
		a->types.push_back(types[0]);
		a->hashes.insert(types[0].hash);
		maxint totalSize = types[0].size;

		for (maxint i = 1; i < count; i++)
		{
			a->types.push_back(types[i]);
			a->hashes.insert(types[i].hash);
			totalSize += types[i].size;

			// Offset for i is determined by how much mem previous takes up
			// Amount of memory is proportional to the type size
			maxint offset = (maxint)(((float64)types[i - 1].size / totalSize) * MEM_16K_BYTES);
			uint8 misalign = offset & (Memory::CACHE_LINE_SIZE - 1);
			a->offsets.push_back(offset - misalign);
		}

		void* alignedPointer = Memory::AlignedMalloc(sizeof(DataChunk), Memory::CACHE_LINE_SIZE);
		a->firstChunk = new (alignedPointer) DataChunk();
		a->firstChunk->archetype = a;
		a->firstChunk->next = nullptr;

		archetypes.push_back(a);

		return a;
	}

	void EntityManager::NewArchetypeInstance(Archetype* a, maxint& outChunk, maxint& outIndex)
	{
		maxint index = a->firstChunk->lastIndex;
		uint8* start = a->firstChunk->data;

		// Engine all types and instantiate them at correct place (non-interleaved)
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
