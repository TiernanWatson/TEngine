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
	typedef uint8_t uint8;
	typedef uint16_t uint16;
	typedef uint32_t uint32;
	typedef uint64_t uint64;

	typedef int8_t int8;
	typedef int16_t int16;
	typedef int32_t int32;
	typedef int64_t int64;

	typedef size_t maxint;

	typedef float float32;
	typedef double float64;

	typedef uintptr_t uintptr;
	typedef intptr_t intptr;
	typedef ptrdiff_t ptrdiff;
}