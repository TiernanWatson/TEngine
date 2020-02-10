#pragma once
#include "../PortableTypes.h"
#include <string>

namespace TEngine 
{
	// 4D vector, 4-byte aligned
	class Vector4
	{
	public:
		F32 x, y, z, w;

	public:
		Vector4() : x(0), y(0), z(0), w(0) {};
		Vector4(F32 x, F32 y, F32 z, F32 w) : x(x), y(y), z(z), w(w) {};

		F32 Magnitude() const;
		F32 SqrMagnitude() const;

		void Normalize();
		Vector4 Normalized() const;

		std::string ToString() const;
	};
}

