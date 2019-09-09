#pragma once
#include "../PortableTypes.h"
#include <string>

namespace TEngine 
{
	/**
	* Class describing a 4D vector, 16-byte aligned
	**/
	class Vector4
	{
	public:
		float32 x, y, z, w;

	public:
		Vector4() : x(0), y(0), z(0), w(0) {};
		Vector4(float32 x, float32 y, float32 z, float32 w) : x(x), y(y), z(z), w(w) {};

		float32 Magnitude() const;
		float32 SqrMagnitude() const;

		void Normalize();
		Vector4 Normalized() const;

		std::string ToString() const;
	};
}

