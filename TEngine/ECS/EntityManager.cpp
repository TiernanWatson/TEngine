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
		for (Archetype* a : archetypes_) 
			delete a;
	}

	U32 EntityManager::NewEntity()
	{
		U32 id;
		if (unused_id_.size() != 0)
		{
			id = unused_id_.front();
			unused_id_.pop();
		}
		else 
		{
			id = entity_count_;
		}

		entity_count_++;
		return id;
	}

	void EntityManager::DeleteEntity(U32 id)
	{
		EntityDetails details = entity_storage_map_[id];

		// TODO: Remove from datachunk

		unused_id_.push(id);
		entity_count_--;
	}

	Archetype* EntityManager::FindArchetype(Metatype* types, USIZE count) const
	{
		for (int i = 0; i < archetypes_.size(); i++)
		{
			if (archetypes_[i]->types.size() != count)
				continue;

			bool matches = true;
			for (int j = 0; j < archetypes_[i]->types.size(); j++)
			{
				if (types[j].hash != archetypes_[i]->types[j].hash)
				{
					matches = false;
					break;
				}
			}

			if (matches) return archetypes_[i];
		}

		return nullptr;
	}

	std::vector<Archetype*> EntityManager::MatchingArchetypes(Metatype* inc, USIZE count) const
	{
		std::vector<Archetype*> result;
		for (USIZE i = 0; i < archetypes_.size(); i++)
		{
			bool matches = true;
			for (USIZE j = 0; j < count; j++)
			{
				if (archetypes_[i]->hashes.find(inc[j].hash) ==
					archetypes_[i]->hashes.end())
				{
					matches = false;
					break;
				}
			}

			if (matches)
				result.push_back(archetypes_[i]);
		}

		return result;
	}

	Archetype* EntityManager::AddArchetype(Metatype* types, USIZE count)
	{
		assert(count != 0);

		Archetype* a = new Archetype();

		// First offset is always 0, so this is outside of loop 
		a->offsets.push_back(0);
		a->types.push_back(types[0]);
		a->hashes.insert(types[0].hash);
		USIZE totalSize = types[0].size;

		for (USIZE i = 1; i < count; i++)
		{
			a->types.push_back(types[i]);
			a->hashes.insert(types[i].hash);
			totalSize += types[i].size;

			// Offset for i is determined by how much mem previous takes kUp
			// Amount of memory is proportional to the type_ size_
			USIZE offset = (USIZE)(((F64)types[i - 1].size / totalSize) * kMem16kBytes);
			U8 misalign = offset & (Memory::kCacheLineSize - 1);
			a->offsets.push_back(offset - misalign);
		}

		void* alignedPointer = Memory::Malloc(sizeof(DataChunk), Memory::kCacheLineSize);
		a->first_chunk = new (alignedPointer) DataChunk();
		a->first_chunk->archetype = a;
		a->first_chunk->next = nullptr;

		archetypes_.push_back(a);

		return a;
	}

	void EntityManager::NewArchetypeInstance(Archetype* a, USIZE& out_chunk, USIZE& out_index)
	{
		USIZE index = a->first_chunk->last_index;
		U8* start = a->first_chunk->data;

		// Engine all types and instantiate them at correct place (non-interleaved)
		for (int i = 0; i < a->types.size(); i++)
		{
			U8* comp = start + a->offsets[i] + a->types[i].size * index;
			a->types[i].construct((void*)comp);
		}

		out_chunk = 0;
		out_index = index;

		a->first_chunk->last_index++;
	}
}
