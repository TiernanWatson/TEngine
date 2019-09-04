#pragma once
#include <cstdint>

namespace TEngine 
{
	#if defined(_MSC_VER)
	#define _FORCE_INLINE_ __forceinline
	#else
	#define _FORCE_INLINE_ inline
	#endif

	// Important to know exactly what size types are for
	// good memory management, and easy to switch out on 
	// different platforms/compilers if needed

	typedef uint8_t uint8;
	typedef uint16_t uint16;
	typedef uint32_t uint32;
	typedef uint64_t uint64;

	typedef int8_t int8;
	typedef int16_t int16;
	typedef int32_t int32;
	typedef int64_t int64;

	typedef size_t size;

	typedef float float32;
	typedef double float64;

	typedef uintptr_t uintptr;
	typedef intptr_t intptr;
}