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
		/*for (Archetype* a : archetypes_) 
			delete a;*/
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
		for (USIZE i = 0; i < archetypes_.Count(); i++)
		{
			bool matches = true;
			for (USIZE j = 0; j < count; j++)
			{
				if (!archetypes_[i].Contains(types[j]))
				{
					matches = false;
					break;
				}
			}

			if (matches) return (Archetype*)&(archetypes_[i]);
		}

		return nullptr;
	}

	std::vector<Archetype*> EntityManager::MatchingArchetypes(Metatype* inc, USIZE count) const
	{
		std::vector<Archetype*> result;
		for (USIZE i = 0; i < archetypes_.Count(); i++)
		{
			bool matches = true;
			for (USIZE j = 0; j < count; j++)
			{
				if (!archetypes_[i].Contains(inc[j]))
				{
					matches = false;
					break;
				}
			}

			if (matches) result.push_back((Archetype*)&archetypes_[i]);
		}

		return result;
	}

	Archetype* EntityManager::AddArchetype(Metatype* types, USIZE count)
	{
		assert(count != 0 && "Tried to add archetype with no types!");

		// TODO: Allocate mem properly!
		USIZE index = archetypes_.Count();
		return new (archetypes_.RawSpace(index)) Archetype(types, count);
	}

	void EntityManager::NewArchetypeInstance(Archetype* a, U32 entity_id)
	{
		assert(a != nullptr && "Tried to make new archetype instance with nullptr");

		DataChunk* chunk = 0;
		USIZE index = 0;

		a->NewInstance(chunk, index);

		entity_storage_map_[entity_id] = EntityDetails{ a, chunk, index };
	}
}
