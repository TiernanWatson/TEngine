#pragma once
#include "../PortableTypes.h"
#include <string>

namespace TEngine 
{
	/**
	* Class describing a 3D vector, 12 size, leave 4 size to properly align
	**/
	class Vector3
	{
	public:
		const static Vector3 up;
		const static Vector3 forward;
		const static Vector3 right;

		const static Vector3 down;
		const static Vector3 back;
		const static Vector3 left;

		const static Vector3 zero;
		const static Vector3 one;

	public:
		float32 x, y, z;

	public:
		Vector3() : x(0), y(0), z(0) {};
		Vector3(float32 x, float32 y, float32 z) : x(x), y(y), z(z) {};

		// General functions

		float32 Magnitude() const;
		float32 SqrMagnitude() const;

		void Normalize();
		Vector3 Normalized() const;

		// Operator functions

		Vector3 operator*(const float32& rhs) const;

		Vector3& operator*=(const float32& rhs);

		Vector3 operator+(const Vector3& rhs) const;
		Vector3 operator-(const Vector3& rhs) const;

		Vector3& operator+=(const Vector3& rhs);
		Vector3& operator-=(const Vector3& rhs);

		std::string ToString() const;
	};
}
