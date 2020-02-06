#pragma once
#include "../PortableTypes.h"

namespace TEngine
{
	class Vector3;

	/**
	* Class describing a 4x4 F32 matrix, 64 byte size_
	**/
	class Matrix4
	{
	public:
		static const Matrix4 kOne;
		static const Matrix4 kIdentity;

	public:
		union {
			F32 flat[16];
			F32 m[4][4];
		};

		Matrix4(); 
		explicit Matrix4(F32 value);
		explicit Matrix4(F32 m11, F32 m12, F32 m13, F32 m14, 
						F32 m21, F32 m22, F32 m23, F32 m24, 
						F32 m31, F32 m32, F32 m33, F32 m34,
						F32 m41, F32 m42, F32 m43, F32 m44);

		F32 Determinant() const;

		Matrix4 Transpose() const;

		Matrix4 Inverse() const;

		bool operator==(const Matrix4& rhs) const;
		bool operator!=(const Matrix4& rhs) const;

		Matrix4 operator+(const Matrix4& rhs) const;
		Matrix4 operator-(const Matrix4& rhs) const;
		Matrix4 operator*(const Matrix4& rhs) const;
		Matrix4 operator*(const F32& rhs) const;

		Matrix4& operator+=(const Matrix4& rhs);
		Matrix4& operator-=(const Matrix4& rhs);
		Matrix4& operator*=(const Matrix4& rhs);
		Matrix4& operator*=(const F32& rhs);

	public:
		/**
		* Used to return the Camera-to-Clip space matrix for rendering
		**/
		static Matrix4 Projection(F32 fov_rad, F32 aspect, F32 far_dist, F32 near_dist);

		/**
		* Computes an orthographic projection matrix
		**/
		static Matrix4 Orthographic(F32 near_dist, F32 far_dist, F32 left, F32 right, F32 bottom, F32 top);

		/**
		* Used to return the Model-to-World space matrix for rendering
		**/
		static Matrix4 ModelToWorld(const Vector3& trans, const Vector3& scale, const Vector3& rotation);

		static Matrix4 RotateX(F32 radians);
		static Matrix4 RotateY(F32 radians);
		static Matrix4 RotateZ(F32 radians);
	};
}
