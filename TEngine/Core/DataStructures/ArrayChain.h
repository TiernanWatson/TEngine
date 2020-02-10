#pragma once
#include "../PortableTypes.h"
#include "../Memory/Memory.h"
#include <functional>

namespace TEngine
{
	// Expanding linked list of arrays sized arr_size
	template<typename Elem, USIZE arr_size = 16>
	class ArrayChain
	{
	public:
		ArrayChain();
		~ArrayChain();

		Elem& operator[](USIZE index);
		const Elem& operator[](USIZE index) const;

		// Creates a new space in the array and returns its pointer
		Elem* RawSpace(USIZE index);

		inline USIZE Count() const
		{
			return elem_count_;
		}

	private:
		struct SubArray
		{
			// U8 so default constructors can be avoided
			U8 data[arr_size * sizeof(Elem)];
			SubArray* next;
		};

		SubArray* first_arr_;
		USIZE elem_count_;
	};

	template<typename Elem, USIZE arr_size>
	inline ArrayChain<Elem, arr_size>::ArrayChain()
		: first_arr_((SubArray*)Memory::Malloc(sizeof(Elem) * arr_size)),
		elem_count_(0)
	{
		first_arr_->next = nullptr;
	}

	template<typename Elem, USIZE arr_size>
	inline ArrayChain<Elem, arr_size>::~ArrayChain()
	{
		SubArray* arr = first_arr_;
		while (arr != nullptr)
		{
			SubArray* to_free = arr;
			arr = arr->next;
			Memory::Free(to_free);
		}
	}

	template<typename Elem, USIZE arr_size>
	inline Elem& ArrayChain<Elem, arr_size>::operator[](USIZE index)
	{
		USIZE arr_num = index / arr_size;

		SubArray* arr = first_arr_;
		while (arr_num != 0)
		{
			if (arr->next == nullptr)
				arr->next = (SubArray*)Memory::Malloc(sizeof(Elem) * arr_size);
			arr = arr->next;
			index -= arr_size;
		}
		return *(Elem*)(arr->data + index * sizeof(Elem));
	}

	template<typename Elem, USIZE arr_size>
	inline const Elem& ArrayChain<Elem, arr_size>::operator[](USIZE index) const
	{
		USIZE arr_num = index / arr_size;

		SubArray* arr = first_arr_;
		while (arr_num != 0)
		{
			if (arr->next == nullptr)
				arr->next = (SubArray*)Memory::Malloc(sizeof(Elem) * arr_size);
			arr = arr->next;
			index -= arr_size;
		}
		return *(Elem*)(arr->data + index * sizeof(Elem));
	}

	template<typename Elem, USIZE arr_size>
	inline Elem* ArrayChain<Elem, arr_size>::RawSpace(USIZE index)
	{
		elem_count_++;
		return &(*this)[index];
	}
}
