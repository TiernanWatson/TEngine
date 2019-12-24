#pragma once
#include "../PortableTypes.h"

namespace TEngine
{
	class Vector3;

	/**
	* Class describing a 4x4 float32 matrix, 64 size
	**/
	class Matrix4
	{
	public:
		static const Matrix4 one;
		static const Matrix4 identity;

	private:
		static const maxint ELEMENTS = 16;
		static const maxint ROWS = 4;

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

		Matrix4 Transpose() const;

		Matrix4 Inverse() const;

		bool operator==(const Matrix4& rhs) const;
		bool operator!=(const Matrix4& rhs) const;

		Matrix4 operator+(const Matrix4& rhs) const;
		Matrix4 operator-(const Matrix4& rhs) const;
		Matrix4 operator*(const Matrix4& rhs) const;
		Matrix4 operator*(const float32& rhs) const;

		Matrix4& operator+=(const Matrix4& rhs);
		Matrix4& operator-=(const Matrix4& rhs);
		Matrix4& operator*=(const Matrix4& rhs);
		Matrix4& operator*=(const float32& rhs);

	public:
		/**
		* Used to return the Camera-to-Clip space matrix for rendering
		**/
		static Matrix4 Projection(float32 fovRad, float32 aspect, float32 farDist, float32 nearDist);

		/**
		* Used to return the Model-to-World space matrix for rendering
		**/
		static Matrix4 ModelToWorld(const Vector3& trans, const Vector3& scale, const Vector3& rotation);

		static Matrix4 RotateX(float32 radians);
		static Matrix4 RotateY(float32 radians);
		static Matrix4 RotateZ(float32 radians);
	};
}
