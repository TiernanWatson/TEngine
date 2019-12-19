#pragma once
#include "../Core/PortableTypes.h"

namespace TEngine
{
	/**
	* Represents a component type for use in an archetype
	* Data chunk knows how much to allocate, etc...
	**/
	struct Metatype
	{
		size hash;

		size bytes;
		uint8 align;

		void* construct;
		void* destruct;

		template<typename T>
		static constexpr Metatype Create();
	};

	template<typename T>
	inline constexpr Metatype Metatype::Create()
	{
		type_info info = typeid(T);
		
		Metatype t;
		t.hash = info.hash_code();
		t.bytes = sizeof(T);
		t.align = alignof(T);

		t.construct = [](void* address) {
			new (address) T();
		};

		t.destruct = [](void* address) {
			((T*)address)->~T();
		};

		return t;
	}
}
