#pragma once
#include "../PortableTypes.h"
#include <string>

namespace TEngine {
	class Vector4
	{
	public:
		f32 x, y, z, w;

	public:
		Vector4() : x(0), y(0), z(0), w(0) {};
		Vector4(f32 x, f32 y, f32 z, f32 w) : x(x), y(y), z(z), w(w) {};
		~Vector4() {};

		f32 Magnitude() const;
		f32 SqrMagnitude() const;

		void Normalize();
		Vector4 Normalized() const;

		std::string ToString() const;
	};
}

