#include "Vector2Int.h"
#include "TMath.h"

namespace TEngine
{
	float32 Vector2Int::Magnitude() const
	{
		return sqrtf(SqrMagnitude());
	}

	float32 Vector2Int::SqrMagnitude() const
	{
		return (float32)x * x + (float32)y * y;
	}

	Vector2Int Vector2Int::operator*(const uint32& rhs) const
	{
		return Vector2Int(rhs * x, rhs * y);
	}

	Vector2Int& Vector2Int::operator*=(const uint32& rhs)
	{
		x *= rhs;
		y *= rhs;

		return *this;
	}

	Vector2Int Vector2Int::operator+(const Vector2Int& rhs) const
	{
		return Vector2Int(x + rhs.x, y + rhs.y);
	}

	Vector2Int Vector2Int::operator-(const Vector2Int& rhs) const
	{
		return Vector2Int(x - rhs.x, y - rhs.y);
	}

	Vector2Int& Vector2Int::operator+=(const Vector2Int& rhs)
	{
		x += rhs.x;
		y += rhs.y;

		return *this;
	}

	Vector2Int& Vector2Int::operator-=(const Vector2Int& rhs)
	{
		x -= rhs.x;
		y -= rhs.y;

		return *this;
	}
}
