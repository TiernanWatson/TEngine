#pragma once
#include "../PortableTypes.h"
#include "Vector3.h"

namespace TEngine
{
	/**
	* Represents a quaternion, 16-size
	**/
	class Quat
	{
	public:
		float32 x, y, z, w;

	public:
		Quat();
		explicit Quat(float32 x, float32 y, float32 z, float32 w);
		explicit Quat(const Vector3& axis, float32 angleRad);

		Quat operator+(const Quat& rhs) const;
		Quat operator-(const Quat& rhs) const;
		Quat operator*(const Quat& rhs) const;
		
		Quat& operator+=(const Quat& rhs);
		Quat& operator-=(const Quat& rhs);
		Quat& operator*=(const Quat& rhs);
	};
}

