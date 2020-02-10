#pragma once
#include "../PortableTypes.h"

namespace TEngine
{
	// 2-Dimensional vector, 8-bytes
	class Vector2
	{
	public:
		F32 x, y;

	public:
		Vector2() : x(0), y(0) {};
		Vector2(F32 x, F32 y) : x(x), y(y) {};

		// General functions

		F32 Magnitude() const;
		F32 SqrMagnitude() const;

		void Normalize();
		Vector2 Normalized() const;

		// Operator functions

		Vector2 operator*(const F32& rhs) const;

		Vector2& operator*=(const F32& rhs);

		Vector2 operator+(const Vector2& rhs) const;
		Vector2 operator-(const Vector2& rhs) const;

		Vector2& operator+=(const Vector2& rhs);
		Vector2& operator-=(const Vector2& rhs);
	};
}
