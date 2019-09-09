#include "Quat.h"
#include "TMath.h"

namespace TEngine
{
	Quat::Quat() : x(0), y(0), z(0), w(0) { }

	Quat::Quat(float32 x, float32 y, float32 z, float32 w)
		: x(x), y(y), z(z), w(w)
	{
	}

	Quat::Quat(const Vector3& axis, float32 angleRad)
	{
		float32 sin = TMath::Sin(angleRad / 2.f);
		float32 cos = TMath::Cos(angleRad / 2.f);

		x = axis.x * sin;
		y = axis.y * sin;
		z = axis.z * sin;
		w = cos;
	}

	Quat Quat::operator+(const Quat& rhs) const
	{
		return Quat(x + rhs.x, y + rhs.y, z + rhs.z, w + rhs.w);
	}

	Quat Quat::operator-(const Quat& rhs) const
	{
		return Quat(x - rhs.x, y - rhs.y, z - rhs.z, w - rhs.w);
	}

	Quat Quat::operator*(const Quat& rhs) const
	{
		return Quat(y * rhs.z - z * rhs.y + rhs.x * w + x * rhs.w,
					z * rhs.x - x * rhs.z + rhs.y * w + y * rhs.w,
					x * rhs.y - y * rhs.x + rhs.z * w + z * rhs.w,
					w * rhs.w - (x * rhs.x + y * rhs.y + z * rhs.z));
	}

	Quat& Quat::operator+=(const Quat& rhs)
	{
		x += rhs.x;
		y += rhs.y;
		z += rhs.z;
		w += rhs.w;

		return *this;
	}

	Quat& Quat::operator-=(const Quat& rhs)
	{
		x -= rhs.x;
		y -= rhs.y;
		z -= rhs.z;
		w -= rhs.w;

		return *this;
	}

	Quat& Quat::operator*=(const Quat& rhs)
	{
		return *this;
	}

}
