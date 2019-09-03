#include "Vector4.h"

namespace TEngine
{
	float32 Vector4::Magnitude() const
	{
		return sqrtf(SqrMagnitude());
	}

	float32 Vector4::SqrMagnitude() const
	{
		return x * x + y * y + z * z + w * w;
	}

	void Vector4::Normalize()
	{
		float32 length = Magnitude();

		x /= length;
		y /= length;
		z /= length;
		w /= length;
	}

	Vector4 Vector4::Normalized() const
	{
		float32 length = Magnitude();

		float32 x = this->x / length;
		float32 y = this->y / length;
		float32 z = this->z / length;
		float32 w = this->w / length;

		return Vector4(x, y, z, w);
	}

	std::string Vector4::ToString() const
	{
		return "(" + std::to_string(x) + ", " + std::to_string(y)
			+ ", " + std::to_string(z) + ", " + std::to_string(w) + ")";
	}
}