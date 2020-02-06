#include "Vector3.h"

namespace TEngine 
{
	// Convenience constants

	const Vector3 Vector3::kUp = Vector3(0.f, 1.f, 0.f);
	const Vector3 Vector3::kRight = Vector3(1.f, 0.f, 0.f);
	const Vector3 Vector3::kForward = Vector3(0.f, 0.f, 1.f);

	const Vector3 Vector3::kDown = Vector3(0.f, -1.f, 0.f);
	const Vector3 Vector3::kLeft = Vector3(-1.f, 0.f, 0.f);
	const Vector3 Vector3::kBack = Vector3(0.f, 0.f, -1.f);

	const Vector3 Vector3::kZero = Vector3();
	const Vector3 Vector3::kOne = Vector3(1.f, 1.f, 1.f);

	// Functions

	F32 Vector3::Magnitude() const
	{
		return sqrtf(SqrMagnitude());
	}

	F32 Vector3::SqrMagnitude() const
	{
		return x * x + y * y + z * z;
	}

	void Vector3::Normalize()
	{
		F32 length = Magnitude();

		x /= length;
		y /= length;
		z /= length;
	}

	Vector3 Vector3::Normalized() const
	{
		F32 length = Magnitude();

		F32 x = this->x / length;
		F32 y = this->y / length;
		F32 z = this->z / length;

		return Vector3(x, y, z);
	}

	Vector3 Vector3::operator*(const F32& rhs) const
	{
		return Vector3(rhs * x, rhs * y, rhs * z);
	}

	Vector3& Vector3::operator*=(const F32& rhs)
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