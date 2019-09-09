#include "Vector3.h"

namespace TEngine 
{
	// Convenience constants

	const Vector3 Vector3::up = Vector3(0.f, 1.f, 0.f);
	const Vector3 Vector3::right = Vector3(-1.f, 0.f, 0.f);
	const Vector3 Vector3::forward = Vector3(0.f, 0.f, 1.f);

	const Vector3 Vector3::down = Vector3(0.f, -1.f, 0.f);
	const Vector3 Vector3::left = Vector3(1.f, 0.f, 0.f);
	const Vector3 Vector3::back = Vector3(0.f, 0.f, -1.f);

	const Vector3 Vector3::zero = Vector3();
	const Vector3 Vector3::one = Vector3(1.f, 1.f, 1.f);

	// Functions

	float32 Vector3::Magnitude() const
	{
		return sqrtf(SqrMagnitude());
	}

	float32 Vector3::SqrMagnitude() const
	{
		return x * x + y * y + z * z;
	}

	void Vector3::Normalize()
	{
		float32 length = Magnitude();

		x /= length;
		y /= length;
		z /= length;
	}

	Vector3 Vector3::Normalized() const
	{
		float32 length = Magnitude();

		float32 x = this->x / length;
		float32 y = this->y / length;
		float32 z = this->z / length;

		return Vector3(x, y, z);
	}

	Vector3 Vector3::operator*(const float32& rhs) const
	{
		return Vector3(rhs * x, rhs * y, rhs * z);
	}

	Vector3& Vector3::operator*=(const float32& rhs)
	{
		x *= rhs;
		y *= rhs;
		z *= rhs;

		return *this;
	}

	Vector3 Vector3::operator+(const Vector3& rhs) const
	{
		return Vector3(x + rhs.x, y + rhs.y, z + rhs.z);
	}

	Vector3 Vector3::operator-(const Vector3& rhs) const
	{
		return Vector3(x - rhs.x, y - rhs.y, z - rhs.z);
	}

	Vector3& Vector3::operator+=(const Vector3& rhs)
	{
		x += rhs.x;
		y += rhs.y;
		z += rhs.z;

		return *this;
	}

	Vector3& Vector3::operator-=(const Vector3& rhs)
	{
		x -= rhs.x;
		y -= rhs.y;
		z -= rhs.z;

		return *this;
	}

	std::string Vector3::ToString() const
	{
		return "(" + std::to_string(x) + ", " + std::to_string(y)
			+ ", " + std::to_string(z) + ")";
	}
}