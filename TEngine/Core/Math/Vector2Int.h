#pragma once
#include "../PortableTypes.h"

namespace TEngine
{
	class Vector2Int
	{
	public:
		U32 x, y;

	public:
		Vector2Int() : x(0), y(0) {};
		Vector2Int(U32 x, U32 y) : x(x), y(y) {};

		// General functions

		F32 Magnitude() const;
		F32 SqrMagnitude() const;

		// Operator functions

		Vector2Int operator*(const U32& rhs) const;

		Vector2Int& operator*=(const U32& rhs);

		Vector2Int operator+(const Vector2Int& rhs) const;
		Vector2Int operator-(const Vector2Int& rhs) const;

		Vector2Int& operator+=(const Vector2Int& rhs);
		Vector2Int& operator-=(const Vector2Int& rhs);
	};
}
