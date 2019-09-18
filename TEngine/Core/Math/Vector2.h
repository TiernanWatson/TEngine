#pragma once
#include "../PortableTypes.h"

namespace TEngine
{
	class Vector2
	{
	public:
		float32 x, y;

	public:
		Vector2() : x(0), y(0) {};
		Vector2(float32 x, float32 y) : x(x), y(y) {};

		// General functions

		float32 Magnitude() const;
		float32 SqrMagnitude() const;

		void Normalize();
		Vector2 Normalized() const;

		// Operator functions

		Vector2 operator*(const float32& rhs) const;

		Vector2& operator*=(const float32& rhs);

		Vector2 operator+(const Vector2& rhs) const;
		Vector2 operator-(const Vector2& rhs) const;

		Vector2& operator+=(const Vector2& rhs);
		Vector2& operator-=(const Vector2& rhs);
	};
}
