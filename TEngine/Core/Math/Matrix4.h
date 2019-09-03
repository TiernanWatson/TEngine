#pragma once
#include "../PortableTypes.h"

namespace TEngine
{
	class Matrix4
	{
	private:
		static const size ELEMENTS = 16;
		static const size ROWS = 4;

	public:
		union {
			float32 flat[ELEMENTS];
			float32 m[ROWS][ROWS];
		};

		Matrix4(); 
		explicit Matrix4(float32 value);
		explicit Matrix4(float32 m11, float32 m12, float32 m13, float32 m14, 
						float32 m21, float32 m22, float32 m23, float32 m24, 
						float32 m31, float32 m32, float32 m33, float32 m34,
						float32 m41, float32 m42, float32 m43, float32 m44);

		float32 Determinant() const;

		bool operator==(const Matrix4& rhs) const;
		bool operator!=(const Matrix4& rhs) const;

		Matrix4 operator+(const Matrix4& rhs) const;
		Matrix4 operator-(const Matrix4& rhs) const;
		Matrix4 operator*(const Matrix4& rhs) const;

		Matrix4& operator+=(const Matrix4& rhs);
		Matrix4& operator-=(const Matrix4& rhs);
		Matrix4& operator*=(const Matrix4& rhs);

	public:
		static const Matrix4 one;
		static const Matrix4 identity;
	};
}
