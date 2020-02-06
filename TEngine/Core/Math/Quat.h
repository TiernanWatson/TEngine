#pragma once
#include "../PortableTypes.h"
#include "Vector3.h"

namespace TEngine
{
	/**
	* Represents a quaternion, 16-size_
	**/
	class Quat
	{
	public:
		F32 x, y, z, w;

	public:
		Quat();
		explicit Quat(F32 x, F32 y, F32 z, F32 w);
		explicit Quat(const Vector3& axis, F32 angleRad);

		Quat operator+(const Quat& rhs) const;
		Quat operator-(const Quat& rhs) const;
		Quat operator*(const Quat& rhs) const;
		
		Quat& operator+=(const Quat& rhs);
		Quat& operator-=(const Quat& rhs);
		Quat& operator*=(const Quat& rhs);
	};
}

