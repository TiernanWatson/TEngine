#include "Vector4.h"

TEngine::f32 TEngine::Vector4::Magnitude() const
{
	return sqrtf(SqrMagnitude());
}

TEngine::f32 TEngine::Vector4::SqrMagnitude() const
{
	return x * x + y * y + z * z + w * w;
}

void TEngine::Vector4::Normalize()
{
	f32 length = Magnitude();

	x /= length;
	y /= length;
	z /= length;
	w /= length;
}

TEngine::Vector4 TEngine::Vector4::Normalized() const
{
	f32 length = Magnitude();

	f32 x = this->x / length;
	f32 y = this->y / length;
	f32 z = this->z / length;
	f32 w = this->w / length;

	return Vector4(x, y, z, w);
}

std::string TEngine::Vector4::ToString() const
{
	return "(" + std::to_string(x) + ", " + std::to_string(y)
		+ ", " + std::to_string(z) + ", " + std::to_string(w) + ")";
}
