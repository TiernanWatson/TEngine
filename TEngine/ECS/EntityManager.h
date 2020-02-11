#pragma once
#include "../Core/PortableTypes.h"
#include "../Core/Exception.h"
#include "../Core/DataStructures/ArrayChain.h"
#include "Metatype.h"
#include "Archetype.h"
#include "DataChunk.h"
#include <queue>
#include <vector>
#include <unordered_map>
#include <functional>

namespace TEngine
{
	// Manages archetypes and entities in a world
	class EntityManager
	{
	public:
		EntityManager();
		~EntityManager();

		U32 NewEntity();
		template<typename ...Comps>
		U32 NewEntityWith();
		template<typename ...Comps>
		U32 NewEntityWith(Comps* ...args);
		
		void DeleteEntity(U32 id);

		template<typename Comp>
		void AddToEntity(U32 id);

		template<typename ...Comps>
		void ForEach(std::function<void(Comps*...)> func);

		template<typename T>
		T& GetComponent(U32 id) const;

	private:
		void NewArchetypeInstance(Archetype* a, U32 entity_id);

		// Gets component of type T at index of chunk
		template<typename T>
		T* GetComponentChunkId(DataChunk* chunk, USIZE index);

		Archetype* FindArchetype(Metatype* types, USIZE count) const;

		std::vector<Archetype*> MatchingArchetypes(Metatype* inc, USIZE count) const;

		Archetype* AddArchetype(Metatype* types, USIZE count);

		struct EntityDetails 
		{
			Archetype* archetype;
			DataChunk* chunk;
			USIZE chunk_index;
		};

		ArrayChain<Archetype> archetypes_;
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
		
		NewArchetypeInstance(a, id);

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

		NewArchetypeInstance(a, id);

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
			DataChunk* chunk = a->first_chunk_;
			while (chunk != nullptr)
			{
				for (USIZE i = 0; i < chunk->last_index; i++)
				{
					func(GetComponentChunkId<Comps>(chunk, i)...);
				}
				chunk = chunk->next;
			}
		}
	}

	template<typename T>
	inline T& EntityManager::GetComponent(U32 id) const
	{
		const EntityDetails& detail = entity_storage_map_.at(id);
		Archetype* archetype = detail.archetype;
		USIZE hash = typeid(T).hash_code();

		if (archetype->hash_type_map_.find(hash) 
			!= archetype->hash_type_map_.end())
		{
			Archetype::Subtype& sub = archetype->hash_type_map_[hash];

			U8* comp = (U8*)archetype->first_chunk_->data
					+ (sub.type.size + sub.padding) * detail.chunk_index
					+ sub.offset;

			return *(T*)comp;
		}

		throw EXCEPTION("Could not find component requested!");
	}

	template<typename T>
	inline T* EntityManager::GetComponentChunkId(DataChunk* chunk, USIZE index)
	{
		Archetype* archetype = chunk->archetype;
		Metatype meta = Metatype::Create<T>();

		Archetype::Subtype& sub = archetype->hash_type_map_[meta.hash];

		U8* comp = (U8*)chunk->data
			+ (sub.type.size + sub.padding) * index
			+ sub.offset;

		return (T*)comp;
	}
}
