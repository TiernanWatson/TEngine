#include "Matrix4.h"
#include "../Math/TMath.h"
#include "Vector3.h"
#include <cstring>
#include "../Exception.h"

namespace TEngine
{
	const Matrix4 Matrix4::one = Matrix4(1.f);
	const Matrix4 Matrix4::identity = Matrix4(1, 0, 0, 0, 
											0, 1, 0, 0,
											0, 0, 1, 0, 
											0, 0, 0, 1);

	Matrix4::Matrix4()
	{
		memset(flat, 0, sizeof(flat));
	}

	Matrix4::Matrix4(float32 value)
	{
		for (float32& f : flat)
			f = value;
	}

	Matrix4::Matrix4(float32 m11, float32 m12, float32 m13, float32 m14, 
					float32 m21, float32 m22, float32 m23, float32 m24, 
					float32 m31, float32 m32, float32 m33, float32 m34, 
					float32 m41, float32 m42, float32 m43, float32 m44)
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

	Matrix4 Matrix4::Transpose() const
	{
		Matrix4 result;

		for (uint8 i = 0; i < 4; i++)
		{
			for (uint8 j = 0; j < 4; j++)
			{
				result.m[i][j] = m[j][i];
			}
		}

		return result;
	}

	Matrix4 Matrix4::Inverse() const
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
		float32 m12 = -flat[1] * flat[10] * flat[15] + flat[1] * flat[11] * flat[14] +
			flat[9] * flat[2] * flat[15] - flat[9] * flat[3] * flat[14] -
			flat[13] * flat[2] * flat[11] + flat[13] * flat[3] * flat[10];
		float32 m22 = flat[0] * flat[10] * flat[15] - flat[0] * flat[11] * flat[14] -
			flat[8] * flat[2] * flat[15] + flat[8] * flat[3] * flat[14] +
			flat[12] * flat[2] * flat[11] - flat[12] * flat[3] * flat[10];
		float32 m32 = -flat[0] * flat[9] * flat[15] + flat[0] * flat[11] * flat[13] +
			flat[8] * flat[1] * flat[15] - flat[8] * flat[3] * flat[13] -
			flat[12] * flat[1] * flat[11] + flat[12] * flat[3] * flat[9];
		float32 m42 = flat[0] * flat[9] * flat[14] - flat[0] * flat[10] * flat[13] -
			flat[8] * flat[1] * flat[14] + flat[8] * flat[2] * flat[13] +
			flat[12] * flat[1] * flat[10] - flat[12] * flat[2] * flat[9];
		float32 m13 = flat[1] * flat[6] * flat[15] - flat[1] * flat[7] * flat[14] -
			flat[5] * flat[2] * flat[15] + flat[5] * flat[3] * flat[14] +
			flat[13] * flat[2] * flat[7] - flat[13] * flat[3] * flat[6];
		float32 m23 = -flat[0] * flat[6] * flat[15] + flat[0] * flat[7] * flat[14] +
			flat[4] * flat[2] * flat[15] - flat[4] * flat[3] * flat[14] -
			flat[12] * flat[2] * flat[7] + flat[12] * flat[3] * flat[6];
		float32 m33 = flat[0] * flat[5] * flat[15] - flat[0] * flat[7] * flat[13] -
			flat[4] * flat[1] * flat[15] + flat[4] * flat[3] * flat[13] +
			flat[12] * flat[1] * flat[7] - flat[12] * flat[3] * flat[5];
		float32 m43 = -flat[0] * flat[5] * flat[14] + flat[0] * flat[6] * flat[13] +
			flat[4] * flat[1] * flat[14] - flat[4] * flat[2] * flat[13] -
			flat[12] * flat[1] * flat[6] + flat[12] * flat[2] * flat[5];
		float32 m14 = -flat[1] * flat[6] * flat[11] + flat[1] * flat[7] * flat[10] +
			flat[5] * flat[2] * flat[11] - flat[5] * flat[3] * flat[10] -
			flat[9] * flat[2] * flat[7] + flat[9] * flat[3] * flat[6];
		float32 m24 = flat[0] * flat[6] * flat[11] - flat[0] * flat[7] * flat[10] -
			flat[4] * flat[2] * flat[11] + flat[4] * flat[3] * flat[10] +
			flat[8] * flat[2] * flat[7] - flat[8] * flat[3] * flat[6];
		float32 m34 = -flat[0] * flat[5] * flat[11] + flat[0] * flat[7] * flat[9] +
			flat[4] * flat[1] * flat[11] - flat[4] * flat[3] * flat[9] -
			flat[8] * flat[1] * flat[7] + flat[8] * flat[3] * flat[5];
		float32 m44 = flat[0] * flat[5] * flat[10] - flat[0] * flat[6] * flat[9] -
			flat[4] * flat[1] * flat[10] + flat[4] * flat[2] * flat[9] +
			flat[8] * flat[1] * flat[6] - flat[8] * flat[2] * flat[5];

		float32 det = flat[0] * m11 + flat[1] * m21 + flat[2] * m31 + flat[3] * m41;

		if (det == 0) 
		{
			throw EXCEPTION("Matrix4::Inverse => Cannot do inverse when the determinant is zero." );
		}

		Matrix4 ret(m11, m12, m13, m14, m21, m22, m23, m24,
					m31, m32, m33, m34, m41, m42, m43, m44);

		return ret * (1.f / det);
	}

	bool Matrix4::operator==(const Matrix4& rhs) const
	{
		for (maxint i = 0; i < 16; i++) {
			if (flat[i] != rhs.flat[i]) 
				return false;
		}

		return true;
	}

	bool Matrix4::operator!=(const Matrix4& rhs) const
	{
		for (maxint i = 0; i < 16; i++) {
			if (flat[i] != rhs.flat[i])
				return true;
		}

		return false;
	}

	Matrix4 Matrix4::operator+(const Matrix4& rhs) const
	{
		Matrix4 ret = Matrix4();

		for (maxint i = 0; i < 16; i++) {
			ret.flat[i] = flat[i] + rhs.flat[i];
		}

		return ret;
	}

	Matrix4 Matrix4::operator-(const Matrix4& rhs) const
	{
		Matrix4 ret = Matrix4();

		for (maxint i = 0; i < 16; i++) {
			ret.flat[i] = flat[i] - rhs.flat[i];
		}

		return ret;
	}

	Matrix4 Matrix4::operator*(const Matrix4& rhs) const
	{
		Matrix4 ret = Matrix4();

		for (maxint i = 0; i < 4; i++) {
			for (maxint j = 0; j < 4; j++) {
				for (maxint k = 0; k < 4; k++) {
					ret.m[i][j] += m[i][k] * rhs.m[k][j];
				}
			}
		}

		return ret;
	}

	Matrix4 Matrix4::operator*(const float32& rhs) const
	{
		Matrix4 result;

		for (int i = 0; i < 16; i++)
		{
			result.flat[i] = flat[i] * rhs;
		}

		return result;
	}

	Matrix4& Matrix4::operator+=(const Matrix4& rhs) 
	{
		for (maxint i = 0; i < 16; i++) {
			flat[i] += rhs.flat[i];
		}
		
		return *this;
	}

	Matrix4& Matrix4::operator-=(const Matrix4& rhs)
	{
		for (maxint i = 0; i < 16; i++) {
			flat[i] -= rhs.flat[i];
		}

		return *this;
	}

	Matrix4& Matrix4::operator*=(const Matrix4& rhs)
	{
		Matrix4 tmp = Matrix4();

		for (maxint i = 0; i < 4; i++) {
			for (maxint j = 0; j < 4; j++) {
				for (maxint k = 0; k < 4; k++) {
					tmp.m[i][j] += m[i][k] * rhs.m[k][j];
				}
			}
		}

		for (maxint i = 0; i < 16; i++) {
			flat[i] = tmp.flat[i];
		}

		return *this;
	}

	Matrix4& Matrix4::operator*=(const float32& rhs)
	{
		for (uint8 i = 0; i < 16; i++)
		{
			flat[i] = flat[i] * rhs;
		}

		return *this;
	}

	Matrix4 Matrix4::Projection(float32 fovRad, float32 aspect, float32 farDist, float32 nearDist)
	{
		Matrix4 result;

		float32 zoomLength = 1 / TMath::Tan(fovRad / 2.f);

		result.m[0][0] = zoomLength / aspect;
		result.m[1][1] = zoomLength;

		result.m[2][2] = (farDist + nearDist) / (nearDist - farDist);
		result.m[2][3] = (2.f * farDist * nearDist) / (nearDist - farDist);

		result.m[3][2] = -1.f;

		return result;
	}

	Matrix4 Matrix4::Orthographic(float32 nearDist, float32 farDist, float32 left, float32 right, float32 bottom, float32 top)
	{
		Matrix4 result;

		result.m[0][0] = 2.f / (right - left);
		result.m[1][1] = 2.f / (top - bottom);
		result.m[2][2] = -2.f / (farDist - nearDist);

		result.m[0][3] = -(right + left) / (right - left);
		result.m[1][3] = -(top + bottom) / (top - bottom);
		result.m[2][3] = -(farDist + nearDist) / (farDist - nearDist);
		result.m[3][3] = 1.f;

		return result;
	}

	Matrix4 Matrix4::ModelToWorld(const Vector3& trans, const Vector3& scale, const Vector3& rotation)
	{
		Matrix4 translate = identity;

		translate.m[0][3] = trans.x;
		translate.m[1][3] = trans.y;
		translate.m[2][3] = trans.z;
		translate.m[3][3] = 1.f;

		Matrix4 scaler = identity;

		scaler.m[0][0] = scale.x;
		scaler.m[1][1] = scale.y;
		scaler.m[2][2] = scale.z;

		Matrix4 rotater = RotateX(rotation.x) * RotateY(rotation.y) * RotateZ(rotation.z);

		return translate * rotater * scaler;
	}

	Matrix4 Matrix4::RotateX(float32 radians) 
	{
		float32 cos = TMath::Cos(radians);
		float32 sin = TMath::Sin(radians);

		return Matrix4(1, 0,    0,   0,  
					   0, cos,  sin, 0,  
					   0, -sin, cos, 0,  
					   0, 0,    0,   1);
	}

	Matrix4 Matrix4::RotateY(float32 radians) 
	{
		float32 cos = TMath::Cos(radians);
		float32 sin = TMath::Sin(radians);

		return Matrix4(cos, 0, -sin, 0,  
					   0,   1, 0,    0,  
					   sin, 0, cos,  0,  
					   0,   0, 0,    1);
	}

	Matrix4 Matrix4::RotateZ(float32 radians) 
	{
		float32 cos = TMath::Cos(radians);
		float32 sin = TMath::Sin(radians);

		return Matrix4(cos,  sin, 0, 0,  
					   -sin, cos, 0, 0,  
					   0,    0,   1, 0,  
					   0,    0,   0, 1);
	}
}