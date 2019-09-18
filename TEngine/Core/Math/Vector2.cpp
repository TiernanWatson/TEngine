#include "Vector2.h"
#include "TMath.h"

namespace TEngine
{
	float32 Vector2::Magnitude() const
	{
		return sqrtf(SqrMagnitude());
	}

	float32 Vector2::SqrMagnitude() const
	{
		return x * x + y * y;
	}

	void Vector2::Normalize()
	{
		float32 length = Magnitude();

		x /= length;
		y /= length;
	}

	Vector2 Vector2::Normalized() const
	{
		float32 length = Magnitude();

		float32 x = this->x / length;
		float32 y = this->y / length;

		return Vector2(x, y);
	}

	Vector2 Vector2::operator*(const float32& rhs) const
	{
		return Vector2(rhs * x, rhs * y);
	}

	Vector2& Vector2::operator*=(const float32& rhs)
	{
		x *= rhs;
		y *= rhs;

		return *this;
	}

	Vector2 Vector2::operator+(const Vector2& rhs) const
	{
		return Vector2(x + rhs.x, y + rhs.y);
	}

	Vector2 Vector2::operator-(const Vector2& rhs) const
	{
		return Vector2(x - rhs.x, y - rhs.y);
	}

	Vector2& Vector2::operator+=(const Vector2& rhs)
	{
		x += rhs.x;
		y += rhs.y;

		return *this;
	}

	Vector2& Vector2::operator-=(const Vector2& rhs)
	{
		x -= rhs.x;
		y -= rhs.y;

		return *this;
	}
}
