#include "Matrix4.h"
#include <cstring>

namespace TEngine
{
	const Matrix4 Matrix4::one = Matrix4(1.f);
	const Matrix4 Matrix4::identity = Matrix4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);

	Matrix4::Matrix4()
	{
		memset(flat, 0, sizeof(flat));
	}

	Matrix4::Matrix4(float32 value)
	{
		for (float32& f : flat)
			f = value;
	}

	Matrix4::Matrix4(float32 m11, float32 m12, float32 m13, float32 m14, float32 m21, float32 m22, float32 m23, float32 m24, float32 m31, float32 m32, float32 m33, float32 m34, float32 m41, float32 m42, float32 m43, float32 m44)
	{
		flat[0] = m11;
		flat[1] = m12;
		flat[2] = m13;
		flat[3] = m14;
		flat[4] = m21;
		flat[5] = m22;
		flat[6] = m23;
		flat[7] = m24;
		flat[8] = m31;
		flat[9] = m32;
		flat[10] = m33;
		flat[11] = m34;
		flat[12] = m41;
		flat[13] = m42;
		flat[14] = m43;
		flat[15] = m44;
	}

	float32 Matrix4::Determinant() const
	{
		float32 m11 = flat[5] * flat[10] * flat[15] - flat[5] * flat[11] * flat[14] -
			flat[9] * flat[6] * flat[15] + flat[9] * flat[7] * flat[14] +
			flat[13] * flat[6] * flat[11] - flat[13] * flat[7] * flat[10];

		float32 m21 = -flat[4] * flat[10] * flat[15] + flat[4] * flat[11] * flat[14] +
			flat[8] * flat[6] * flat[15] - flat[8] * flat[7] * flat[14] -
			flat[12] * flat[6] * flat[11] + flat[12] * flat[7] * flat[10];

		float32 m31 = flat[4] * flat[9] * flat[15] - flat[4] * flat[11] * flat[13] -
			flat[8] * flat[5] * flat[15] + flat[8] * flat[7] * flat[13] +
			flat[12] * flat[5] * flat[11] - flat[12] * flat[7] * flat[9];

		float32 m41 = -flat[4] * flat[9] * flat[14] + flat[4] * flat[10] * flat[13] +
			flat[8] * flat[5] * flat[14] - flat[8] * flat[6] * flat[13] -
			flat[12] * flat[5] * flat[10] + flat[12] * flat[6] * flat[9];

		return flat[0] * m11 + flat[1] * m21 + flat[2] * m31 + flat[3] * m41;
	}

	bool Matrix4::operator==(const Matrix4& rhs) const
	{
		for (size i = 0; i < ELEMENTS; i++) {
			if (flat[i] != rhs.flat[i]) 
				return false;
		}

		return true;
	}

	bool Matrix4::operator!=(const Matrix4& rhs) const
	{
		for (size i = 0; i < ELEMENTS; i++) {
			if (flat[i] != rhs.flat[i])
				return true;
		}

		return false;
	}

	Matrix4 Matrix4::operator+(const Matrix4& rhs) const
	{
		Matrix4 ret = Matrix4();

		for (size i = 0; i < ELEMENTS; i++) {
			ret.flat[i] = flat[i] + rhs.flat[i];
		}

		return ret;
	}

	Matrix4 Matrix4::operator-(const Matrix4& rhs) const
	{
		Matrix4 ret = Matrix4();

		for (size i = 0; i < ELEMENTS; i++) {
			ret.flat[i] = flat[i] - rhs.flat[i];
		}

		return ret;
	}

	Matrix4 Matrix4::operator*(const Matrix4& rhs) const
	{
		Matrix4 ret = Matrix4();

		for (size i = 0; i < ROWS; i++) {
			for (size j = 0; j < ROWS; j++) {
				for (size k = 0; k < ROWS; k++) {
					ret.m[i][j] += m[i][k] * rhs.m[k][j];
				}
			}
		}

		return ret;
	}

	Matrix4& Matrix4::operator+=(const Matrix4& rhs) 
	{
		for (size i = 0; i < ELEMENTS; i++) {
			flat[i] += rhs.flat[i];
		}
		
		return *this;
	}

	Matrix4& Matrix4::operator-=(const Matrix4& rhs)
	{
		for (size i = 0; i < ELEMENTS; i++) {
			flat[i] -= rhs.flat[i];
		}

		return *this;
	}

	Matrix4& Matrix4::operator*=(const Matrix4& rhs)
	{
		Matrix4 tmp = Matrix4();

		for (size i = 0; i < ROWS; i++) {
			for (size j = 0; j < ROWS; j++) {
				for (size k = 0; k < ROWS; k++) {
					tmp.m[i][j] += m[i][k] * rhs.m[k][j];
				}
			}
		}

		for (size i = 0; i < ELEMENTS; i++) {
			flat[i] = tmp.flat[i];
		}

		return *this;
	}

}