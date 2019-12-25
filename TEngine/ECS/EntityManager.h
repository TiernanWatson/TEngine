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
	* Manages entities in the world - use to add/edit/remove comps/ents
	**/
	class EntityManager
	{
	public:
		EntityManager();

		/**
		* Creates a new entity with no components
		**/
		uint32 NewEntity();

		/**
		* Creates an entity with the specified components
		**/
		template<typename ...Comps>
		uint32 NewEntityWith();

		/**
		* Creates an entity with the specified components and instances
		**/
		template<typename ...Comps>
		uint32 NewEntityWith(Comps ...args);

		/**
		* Removes an entity and its associated components
		**/
		void DeleteEntity(uint32 id);

		/**
		* Adds a new component to an entity (warning: will change its archetype)
		**/
		template<typename Comp>
		void AddToEntity(uint32 id);

		/**
		* Returns the archetype that exactly matches the list of metatypes, nullptr if none found
		**/
		Archetype* FindArchetype(Metatype* types, maxint count) const;

		/**
		* Adds a new archetype describing the metatypes and returns a pointer to it
		**/
		Archetype* AddArchetype(Metatype* types, maxint count);

		/**
		* Applies the supplied function to the archetypes containing the metatypes
		**/
		template<typename ...Comps>
		void ForEach(std::function<void(Comps*...)> func);

		/**
		* Gets a reference the component of type T for entity id
		**/
		template<typename T>
		T& GetComponent(uint32 id) const;

		static EntityManager& Main();

	private:
		void NewArchetypeInstance(Archetype* a, maxint& outChunk, maxint& outIndex);

		template<typename T>
		T* GetComponentChunkId(DataChunk* chunk, maxint id);

		struct EntityDetails 
		{
			Archetype* archetype;
			maxint chunk;
			maxint index;
		};

		std::vector<Archetype*> archetypes;

		std::unordered_map<uint32, EntityDetails> entityStorageMap;

		std::queue<uint32> unusedID;

		uint32 entityCount = 0;
	};

	template<typename ...Comps>
	inline uint32 EntityManager::NewEntityWith()
	{
		uint32 id = NewEntity();

		maxint count = sizeof...(Comps);
		Metatype types[] = { Metatype::Create<Comps>()... };

		Archetype* a = FindArchetype(types, count);

		if (a == nullptr) a = AddArchetype(types, count);
		
		maxint chunk, index;
		NewArchetypeInstance(a, chunk, index);

		entityStorageMap[id] = EntityDetails{ a, chunk, index };

		return id;
	}

	template<typename ...Comps>
	inline uint32 EntityManager::NewEntityWith(Comps ...args)
	{
		uint32 id = NewEntity();

		maxint count = sizeof...(Comps);
		Metatype types[] = { Metatype::Create<Comps>()... };

		Archetype* a = FindArchetype(types, count);

		if (a == nullptr) a = AddArchetype(types, count);

		maxint chunk, index;
		NewArchetypeInstance(a, chunk, index);

		entityStorageMap[id] = EntityDetails{ a, chunk, index };

		return id;
	}

	template<typename Comp>
	inline void EntityManager::AddToEntity(uint32 id)
	{
		
	}

	template<typename ...Comps>
	inline void EntityManager::ForEach(std::function<void(Comps*...)> func)
	{
		maxint count = sizeof...(Comps);
		Metatype types[] = { Metatype::Create<Comps>()... };

		Archetype* a = FindArchetype(types, count);
		
		DataChunk* d = a->firstChunk;
		for (maxint i = 0; i < d->lastIndex; i++)
		{
			func(GetComponentChunkId<Comps>(d, i)...);
		}
	}

	template<typename T>
	inline T& EntityManager::GetComponent(uint32 id) const
	{
		const EntityDetails& detail = entityStorageMap.at(id);
		std::vector<Metatype>& types = detail.archetype->types;
		DataChunk* chunk = detail.archetype->firstChunk;

		maxint hash = typeid(T).hash_code();

		maxint index = -1;
		for (maxint i = 0; i < types.size(); i++)
		{
			if (hash == types[i].hash)
			{
				index = i;
				break;
			}
		}

		assert(index != -1);

		uint8* p = (uint8*)chunk->data			// data start
			+ detail.archetype->offsets[index]  // subarray for T
			+ detail.index * sizeof(T);			// entity position

		return *(T*)p;
	}

	template<typename T>
	inline T* EntityManager::GetComponentChunkId(DataChunk* chunk, maxint id)
	{
		Archetype* a = chunk->archetype;

		maxint hash = typeid(T).hash_code();

		for (maxint i = 0; i < a->types.size(); i++)
		{
			if (hash == a->types[i].hash)
			{
				maxint offset = a->offsets[i];
				uint8* p = chunk->data + offset + sizeof(T) * id;
				return (T*)p;
			}
		}

		return nullptr;
	}
}
