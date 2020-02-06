#pragma once
#include <cstdint>
#include <assert.h>
#include "../Helpers/Debug.h"

#if defined(_MSC_VER)
#define _FORCE_INLINE_ __forceinline
#elif defined(__GNUC__)
#define _FORCE_INLINE_ __attribute__((always_inline))
#else
#define _FORCE_INLINE_ inline
#endif

namespace TEngine 
{
	typedef uint8_t U8;
	typedef uint16_t U16;
	typedef uint32_t U32;
	typedef uint64_t U64;

	typedef int8_t I8;
	typedef int16_t I16;
	typedef int32_t I32;
	typedef int64_t I64;

	typedef size_t USIZE;

	typedef float F32;
	typedef double F64;

	typedef uintptr_t UPTR;
	typedef intptr_t IPTR;
	typedef ptrdiff_t PTRDIFF;

	typedef wchar_t wchar;
}