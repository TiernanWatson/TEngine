#pragma once
#include "../Core/PortableTypes.h"
#include "Metatype.h"
#include "Archetype.h"
#include "DataChunk.h"
#include <queue>
#include <vector>
#include <unordered_map>
#include <functional>

namespace TEngine
{
	/**
	* Manages entities_ in the world_ - use to add/edit/remove comps/ents
	**/
	class EntityManager
	{
	public:
		EntityManager();
		~EntityManager();

		/**
		* Creates a new entity with no components
		**/
		U32 NewEntity();

		/**
		* Creates an entity with the specified components
		**/
		template<typename ...Comps>
		U32 NewEntityWith();

		/**
		* Creates an entity with the specified components and instances
		**/
		template<typename ...Comps>
		U32 NewEntityWith(Comps* ...args);

		/**
		* Removes an entity and its associated components
		**/
		void DeleteEntity(U32 id);

		/**
		* Adds a new component to an entity (warning: will change its archetype)
		**/
		template<typename Comp>
		void AddToEntity(U32 id);

		/**
		* Applies the supplied function to the archetypes_ containing the specified types
		**/
		template<typename ...Comps>
		void ForEach(std::function<void(Comps*...)> func);

		/**
		* Gets a reference the component of type_ T for entity index
		**/
		template<typename T>
		T& GetComponent(U32 id) const;

	private:
		/**
		* Instantiates an instance_ of an archetype in the next available slot
		**/
		void NewArchetypeInstance(Archetype* a, USIZE& out_chunk, USIZE& out_index);

		/**
		* Gets a component of type_ T from chunk at index index
		**/
		template<typename T>
		T* GetComponentChunkId(DataChunk* chunk, USIZE index);

		/**
		* Returns the archetype that exactly matches the list of metatypes, nullptr if none found
		**/
		Archetype* FindArchetype(Metatype* types, USIZE count) const;

		/**
		* Returns all the archetypes_ that contain the specified metatypes
		**/
		std::vector<Archetype*> MatchingArchetypes(Metatype* inc, USIZE count) const;

		/**
		* Adds a new archetype describing the metatypes and returns a pointer to it
		**/
		Archetype* AddArchetype(Metatype* types, USIZE count);

		struct EntityDetails 
		{
			Archetype* archetype;
			USIZE chunk;
			USIZE index;
		};

		std::vector<Archetype*> archetypes_;

		std::unordered_map<U32, EntityDetails> entity_storage_map_;

		std::queue<U32> unused_id_;

		U32 entity_count_ = 0;
	};

	template<typename ...Comps>
	inline U32 EntityManager::NewEntityWith()
	{
		U32 id = NewEntity();

		USIZE count = sizeof...(Comps);
		Metatype types[] = { Metatype::Create<Comps>()... };

		Archetype* a = FindArchetype(types, count);

		if (a == nullptr) a = AddArchetype(types, count);
		
		USIZE chunk, index;
		NewArchetypeInstance(a, chunk, index);

		entity_storage_map_[id] = EntityDetails{ a, chunk, index };

		return id;
	}

	template<typename ...Comps>
	inline U32 EntityManager::NewEntityWith(Comps* ...args)
	{
		U32 id = NewEntity();

		USIZE count = sizeof...(Comps);
		Metatype types[] = { Metatype::Create<Comps>()... };

		Archetype* a = FindArchetype(types, count);

		if (a == nullptr) a = AddArchetype(types, count);

		USIZE chunk, index;
		NewArchetypeInstance(a, chunk, index);

		entity_storage_map_[id] = EntityDetails{ a, chunk, index };

		return id;
	}

	template<typename Comp>
	inline void EntityManager::AddToEntity(U32 id)
	{
		
	}

	template<typename ...Comps>
	inline void EntityManager::ForEach(std::function<void(Comps*...)> func)
	{
		USIZE count = sizeof...(Comps);
		Metatype types[] = { Metatype::Create<Comps>()... };

		std::vector<Archetype*> results = MatchingArchetypes(types, count);
		
		for (Archetype* a : results)
		{
			DataChunk* d = a->first_chunk;
			while (d != nullptr)
			{
				for (USIZE i = 0; i < d->last_index; i++)
				{
					func(GetComponentChunkId<Comps>(d, i)...);
				}
				d = d->next;
			}
		}
	}

	template<typename T>
	inline T& EntityManager::GetComponent(U32 id) const
	{
		const EntityDetails& detail = entity_storage_map_.at(id);
		std::vector<Metatype>& types = detail.archetype->types;
		DataChunk* chunk = detail.archetype->first_chunk;

		USIZE hash = typeid(T).hash_code();

		USIZE index = 0;
		for (USIZE i = 0; i < types.size(); i++)
		{
			if (hash == types[i].hash)
			{
				index = i;
				break;
			}
		}

		U8* p = (U8*)chunk->data			// data_ start
			+ detail.archetype->offsets[index]  // subarray for T
			+ detail.index * sizeof(T);			// entity position

		return *(T*)p;
	}

	template<typename T>
	inline T* EntityManager::GetComponentChunkId(DataChunk* chunk, USIZE index)
	{
		Archetype* a = chunk->archetype;

		USIZE hash = typeid(T).hash_code();

		for (USIZE i = 0; i < a->types.size(); i++)
		{
			if (hash == a->types[i].hash)
			{
				U8* p = chunk->data		// data_ start
					+ a->offsets[i]			// subarray for T
					+ sizeof(T) * index;	// entity position

				return (T*)p;
			}
		}

		return nullptr;
	}
}
