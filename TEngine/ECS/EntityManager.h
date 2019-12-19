#pragma once
#include "../Core/PortableTypes.h"
#include "Metatype.h"
#include "Archetype.h"
#include "DataChunk.h"
#include <queue>
#include <vector>

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
		Archetype* FindArchetype(Metatype** types, size count);

		//void ForEach()

		static EntityManager& Main();

	private:
		std::vector<Archetype> archetypes;

		std::queue<uint32> unusedID;

		size entityCount = 0;
	};

	template<typename ...Comps>
	inline uint32 EntityManager::NewEntityWith()
	{
		uint32 id = NewEntity();

		size count = sizeof...(Comps);
		Metatype types[] = { Metatype::Create<Comps>()... };

		Archetype* a = FindArchetype(&types, count);

		if (a == nullptr)
		{
			a = new Archetype();

			for (Metatype& t : types)
				a->types.push_back(t);

			a->firstChunk = new DataChunk();
			a->firstChunk->archetype = a;
			a->firstChunk->next = nullptr;

			archetypes.push_back(a);
		}
		
		uint8* p = a->firstChunk->data;
		for (int i = 0; i < a->types.size(); i++)
		{
			a->types[i].construct((void*)p);
			p += a->types[i].bytes;
		}

		return id;
	}

	template<typename Comp>
	inline void EntityManager::AddToEntity(uint32 id)
	{
		
	}
}
