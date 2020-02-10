#pragma once
#include "../Core/PortableTypes.h"
#include "Metatype.h"
#include <vector>
#include <map>

namespace TEngine
{
	struct DataChunk;

	// A collection of component metatypes e.g. <position, velocity>
	class Archetype
	{
	public:
		Archetype() = delete;
		Archetype(Metatype* metatypes, USIZE count);
		Archetype(const Archetype&) = delete;
		Archetype& operator=(const Archetype&) = delete;
		~Archetype();

		void NewInstance(DataChunk*& out_chunk, USIZE& out_index);

		inline bool Contains(Metatype& metatype) const
		{
			return hash_type_map_.find(metatype.hash) != hash_type_map_.end();
		}

	private:
		struct Subtype
		{
			Metatype type;
			USIZE offset;
			U8 padding;
		};

		// Used when accessing pairs in map
		typedef std::pair<USIZE, Subtype> HashTypePair;

		std::map<USIZE, Subtype> hash_type_map_;
		DataChunk* first_chunk_;
		USIZE total_size_of_comps_;
		USIZE max_items_per_chunk_;

		friend class EntityManager;
	};
}
