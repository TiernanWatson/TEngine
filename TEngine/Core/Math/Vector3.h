#pragma once
#include "../PortableTypes.h"
#include <string>

namespace TEngine 
{
	class Vector3
	{
	public:
		float32 x, y, z;

	public:
		Vector3() : x(0), y(0), z(0) {};
		Vector3(float32 x, float32 y, float32 z) : x(x), y(y), z(z) {};
		~Vector3() {};

		float32 Magnitude() const;
		float32 SqrMagnitude() const;

		void Normalize();
		Vector3 Normalized() const;

		std::string ToString() const;

	public:
		const static Vector3 up;
		const static Vector3 forward;
		const static Vector3 right;

		const static Vector3 down;
		const static Vector3 back;
		const static Vector3 left;

		const static Vector3 zero;
		const static Vector3 one;
	};
}
