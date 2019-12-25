#pragma once
#include "../PortableTypes.h"

namespace TEngine
{
	class Vector2Int
	{
	public:
		uint32 x, y;

	public:
		Vector2Int() : x(0), y(0) {};
		Vector2Int(uint32 x, uint32 y) : x(x), y(y) {};

		// General functions

		float32 Magnitude() const;
		float32 SqrMagnitude() const;

		// Operator functions

		Vector2Int operator*(const uint32& rhs) const;

		Vector2Int& operator*=(const uint32& rhs);

		Vector2Int operator+(const Vector2Int& rhs) const;
		Vector2Int operator-(const Vector2Int& rhs) const;

		Vector2Int& operator+=(const Vector2Int& rhs);
		Vector2Int& operator-=(const Vector2Int& rhs);
	};
}
