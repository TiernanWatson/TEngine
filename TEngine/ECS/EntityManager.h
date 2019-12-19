#pragma once
#include "../Core/PortableTypes.h"
#include "Metatype.h"
#include "Archetype.h"
#include "DataChunk.h"
#include <queue>
#include <vector>
#include <unordered_map>

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
		* Removes an entity and its associated components
		**/
		void DeleteEntity(uint32 id);

		/**
		* Adds a new component to an entity (warning: will change its archetype)
		**/
		template<typename Comp>
		void AddToEntity(uint32 id);

		/**
		* Returns the archetype that matches the list of metatypes, nullptr if none found
		**/
		Archetype* FindArchetype(Metatype* types, size count);

		/**
		* Adds a new archetype descriving the metatypes and returns a pointer to it
		**/
		Archetype* AddArchetype(Metatype* types, size count);

		//void ForEach()

		static EntityManager& Main();

	private:
		void* NewArchetypeInstance(Archetype* a, size& outChunk, size& outIndex);

		struct EntityDetails 
		{
			Archetype* archetype;
			size chunk;
			size index;
		};

		std::vector<Archetype*> archetypes;

		std::unordered_map<uint32, EntityDetails> entityStorageMap;

		std::queue<uint32> unusedID;

		size entityCount = 0;
	};

	template<typename ...Comps>
	inline uint32 EntityManager::NewEntityWith()
	{
		uint32 id = NewEntity();

		size count = sizeof...(Comps);
		Metatype types[] = { Metatype::Create<Comps>()... };

		Archetype* a = FindArchetype(types, count);

		if (a == nullptr) a = AddArchetype(types, count);
		
		size chunk, index;
		NewArchetypeInstance(a, chunk, index);

		entityStorageMap[id] = EntityDetails{ a, chunk, index };

		return id;
	}

	template<typename Comp>
	inline void EntityManager::AddToEntity(uint32 id)
	{
		
	}
}
