#pragma once
#include "../PortableTypes.h"
#include <string>

namespace TEngine 
{
	// 3D vector, 12 bytes, 4 byte alignment
	class Vector3
	{
	public:
		const static Vector3 kUp;
		const static Vector3 kForward;
		const static Vector3 kRight;

		const static Vector3 kDown;
		const static Vector3 kBack;
		const static Vector3 kLeft;

		const static Vector3 kZero;
		const static Vector3 kOne;

	public:
		F32 x, y, z;

	public:
		Vector3() : x(0), y(0), z(0) {};
		Vector3(F32 x, F32 y, F32 z) : x(x), y(y), z(z) {};

		// General functions

		F32 Magnitude() const;
		F32 SqrMagnitude() const;

		void Normalize();
		Vector3 Normalized() const;

		// Operator functions

		Vector3 operator*(const F32& rhs) const;

		Vector3& operator*=(const F32& rhs);

		Vector3 operator+(const Vector3& rhs) const;
		Vector3 operator-(const Vector3& rhs) const;

		Vector3& operator+=(const Vector3& rhs);
		Vector3& operator-=(const Vector3& rhs);

		std::string ToString() const;
	};
}
