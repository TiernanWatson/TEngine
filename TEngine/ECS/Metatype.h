#pragma once
#include "../Core/PortableTypes.h"
#include <functional>
#include <typeinfo>

namespace TEngine
{
	/**
	* Represents a component type_ for use in an archetype
	* Data chunk knows how much to allocate, etc...
	**/
	struct Metatype
	{
		USIZE hash;
		USIZE size;
		U8 align;

		std::function<void(void*)> construct;
		std::function<void(void*)> destruct;

		std::function<void(void*, void*)> copy;

		template<typename T>
		static constexpr Metatype Create();
	};

	template<typename T>
	inline constexpr Metatype Metatype::Create()
	{
		const type_info& info = typeid(T);
		
		Metatype t;
		t.hash = info.hash_code();
		t.size = sizeof(T);
		t.align = alignof(T);

		t.construct = [](void* address) {
			new (address) T();
		};

		t.destruct = [](void* address) {
			((T*)address)->~T();
		};

		t.copy = [](void* dest, void* src) {
			memcpy(dest, src, sizeof(T));
		};

		return t;
	}
}
