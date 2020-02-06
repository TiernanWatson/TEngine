#include "Vector4.h"

namespace TEngine
{
	F32 Vector4::Magnitude() const
	{
		return sqrtf(SqrMagnitude());
	}

	F32 Vector4::SqrMagnitude() const
	{
		return x * x + y * y + z * z + w * w;
	}

	void Vector4::Normalize()
	{
		F32 length = Magnitude();

		x /= length;
		y /= length;
		z /= length;
		w /= length;
	}

	Vector4 Vector4::Normalized() const
	{
		F32 length = Magnitude();

		F32 x = this->x / length;
		F32 y = this->y / length;
		F32 z = this->z / length;
		F32 w = this->w / length;

		return Vector4(x, y, z, w);
	}

	std::string Vector4::ToString() const
	{
		return "(" + std::to_string(x) + ", " + std::to_string(y)
			+ ", " + std::to_string(z) + ", " + std::to_string(w) + ")";
	}
}