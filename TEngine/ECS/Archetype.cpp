#include "Archetype.h"
#include "DataChunk.h"
#include "../Core/Exception.h"
#include "../Core/Memory/Memory.h"
#include "../Core/Math/TMath.h"

namespace TEngine
{
	Archetype::Archetype(Metatype* metatypes, USIZE count)
		: first_chunk_((DataChunk*)Memory::Malloc(sizeof(DataChunk))),
		total_size_of_comps_(0)
	{
		if (first_chunk_ == NULL)
			throw EXCEPTION("Could not allocate memory for archetype");

		for (USIZE i = 0; i < count; i++)
			total_size_of_comps_ += metatypes[i].size;

		first_chunk_->archetype = this;
		first_chunk_->last_index = 0;
		first_chunk_->next = nullptr;

		// Setup each component info (offsets, padding, etc...)
		USIZE offset_accum = 0, max_items = -1;
		for (U8 i = 0; i < count; i++)
		{
			F64 mem_fraction = (F32)metatypes[i].size / total_size_of_comps_;
			USIZE test_size = (USIZE)(mem_fraction * kChunkDataSize);
			USIZE test_offset = offset_accum;

			U8 misalign = test_offset & (Memory::kCacheLineSize - 1);
			U8 correction = misalign != 0 ? (Memory::kCacheLineSize - misalign) : 0;
			USIZE final_offset = test_offset + correction;

			// Padding satisfies normal alignment (e.g. 12 byte comp in 16 bytes)
			misalign = metatypes[i].size & (metatypes[i].align - 1);
			U8 padding = misalign != 0 ? (metatypes[i].align - misalign) : 0;
			
			hash_type_map_[metatypes[i].hash] = Subtype{ metatypes[i], final_offset, padding };

			USIZE max_comp = (F64)(test_size - correction) / (metatypes[i].size + padding);
			max_items = TMath::Min(max_comp, max_items);

			offset_accum += test_size;
		}

		max_items_per_chunk_ = max_items;
	}

	Archetype::~Archetype()
	{
		DataChunk* chunk = first_chunk_;
		while (chunk != nullptr)
		{
			DataChunk* to_free = chunk;
			chunk = chunk->next;
			Memory::Free(to_free);
		}
	}

	void Archetype::NewInstance(DataChunk*& out_chunk, USIZE& out_index)
	{
		USIZE index = first_chunk_->last_index;
		U8* start = first_chunk_->data;

		// Instantiate all components at correct location
		for (const HashTypePair& s : hash_type_map_)
		{
			const Subtype& t = s.second;
			USIZE total_size = t.type.size + t.padding;
			U8* comp_ptr = start + t.offset + (total_size * index);
			t.type.construct((void*)comp_ptr);
		}

		out_chunk = first_chunk_;
		out_index = index;

		first_chunk_->last_index++;

		// TODO: Support multiple chunks!
	}
}
