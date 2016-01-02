//------------------------------------------------------------
// <copyright file="Matrix4.cpp" autor="Markus Perz">
//     Copyright (c) Markus Perz. All rights reserved.
// </copyright>
//------------------------------------------------------------

#include <Teaser/Math/Matrix4.hpp>

namespace Teaser
{

const Matrix4 Matrix4::Identity = Matrix4(Vector4(1, 0, 0, 0),
                                          Vector4(0, 1, 0, 0),
                                          Vector4(0, 0, 1, 0),
                                          Vector4(0, 0, 0, 1));

Matrix4& Matrix4::operator*=(f32 f)
{
	for (int i = 0; i < 4; i++)
	{
		m[i] *= f;
	}
	return *this;
}

Matrix4& Matrix4::operator/=(f32 f)
{
	for (int i = 0; i < 4; i++)
	{
		m[i] /= f;
	}
	return *this;
}

bool Matrix4::operator!=(const Matrix4& other) const
{
	return !(*this == other);
}

bool Matrix4::operator==(const Matrix4& other) const
{
	for (u8 i = 0; i < 4; i++)
	{
		if (m[i] != other[i])
			return false;
	}
	return true;
}
f32 Matrix4::getDeterminant() const
{

	// clang-format off
	f32 det =
		m00*m11*m22*m33 + m00*m21*m32*m13 + m00*m31*m12*m23 +
		m10*m01*m32*m23 + m10*m21*m02*m33 + m10*m31*m22*m03 +
		m20*m01*m12*m33 + m20*m11*m32*m03 + m20*m31*m02*m13 +
		m30*m01*m22*m13 + m30*m11*m02*m23 + m30*m21*m12*m03 -

		m00*m11*m32*m23 - m00*m21*m12*m33 - m00*m31*m22*m13 -
		m10*m01*m22*m33 - m10*m21*m32*m03 - m10*m31*m02*m23 -
		m20*m01*m32*m13 - m20*m11*m02*m33 - m20*m31*m12*m03 -
		m30*m01*m12*m23 - m30*m11*m22*m03 - m30*m21*m02*m13;

	return det;
	// clang-format on
}

Matrix4& Matrix4::operator *=(const Matrix4& other) 
{
	return *this = *this*other;
}

std::ostream& operator<<(std::ostream& stream, const Matrix4& other)
{
	stream << "Matrix4( " << std::setw(6) << other.m00 << std::setw(6)
	       << other.m10 << std::setw(6) << other.m20 << std::setw(6)
	       << other.m30 << std::endl

	       << std::setw(15) << other.m01 << std::setw(6) << other.m11
	       << std::setw(6) << other.m21 << std::setw(6) << other.m31
	       << std::endl

	       << std::setw(15) << other.m02 << std::setw(6) << other.m12
	       << std::setw(6) << other.m22 << std::setw(6) << other.m32
	       << std::endl

	       << std::setw(15) << other.m03 << std::setw(6) << other.m13
	       << std::setw(6) << other.m23 << std::setw(6) << other.m33 << ")"
	       << std::endl;

	return stream;
}

Matrix4 operator+(const Matrix4& lhs, const Matrix4& rhs)
{

	Matrix4 result;
	for (u8 col = 0; col < 4; col++)
	{
		for (u8 row = 0; row < 4; row++)
		{
			result[col][row] = lhs[col][row] + rhs[col][row];
		}
	}
	return result;
}

Matrix4& Matrix4::invert()
{

	Matrix4 other = getInverse();

	for (u8 i = 0; i < 4; i++)
	{
		m[i] = other[i];
	}
	return *this;
}

// Copied from gingerBill Dunjun at Github
Matrix4 Matrix4::getInverse() const
{
	const f32 coef00 = m[2][2] * m[3][3] - m[3][2] * m[2][3];
	const f32 coef02 = m[1][2] * m[3][3] - m[3][2] * m[1][3];
	const f32 coef03 = m[1][2] * m[2][3] - m[2][2] * m[1][3];
	const f32 coef04 = m[2][1] * m[3][3] - m[3][1] * m[2][3];
	const f32 coef06 = m[1][1] * m[3][3] - m[3][1] * m[1][3];
	const f32 coef07 = m[1][1] * m[2][3] - m[2][1] * m[1][3];
	const f32 coef08 = m[2][1] * m[3][2] - m[3][1] * m[2][2];
	const f32 coef10 = m[1][1] * m[3][2] - m[3][1] * m[1][2];
	const f32 coef11 = m[1][1] * m[2][2] - m[2][1] * m[1][2];
	const f32 coef12 = m[2][0] * m[3][3] - m[3][0] * m[2][3];
	const f32 coef14 = m[1][0] * m[3][3] - m[3][0] * m[1][3];
	const f32 coef15 = m[1][0] * m[2][3] - m[2][0] * m[1][3];
	const f32 coef16 = m[2][0] * m[3][2] - m[3][0] * m[2][2];
	const f32 coef18 = m[1][0] * m[3][2] - m[3][0] * m[1][2];
	const f32 coef19 = m[1][0] * m[2][2] - m[2][0] * m[1][2];
	const f32 coef20 = m[2][0] * m[3][1] - m[3][0] * m[2][1];
	const f32 coef22 = m[1][0] * m[3][1] - m[3][0] * m[1][1];
	const f32 coef23 = m[1][0] * m[2][1] - m[2][0] * m[1][1];

	const Vector4 fac0 = {coef00, coef00, coef02, coef03};
	const Vector4 fac1 = {coef04, coef04, coef06, coef07};
	const Vector4 fac2 = {coef08, coef08, coef10, coef11};
	const Vector4 fac3 = {coef12, coef12, coef14, coef15};
	const Vector4 fac4 = {coef16, coef16, coef18, coef19};
	const Vector4 fac5 = {coef20, coef20, coef22, coef23};

	const Vector4 vec0 = {m[1][0], m[0][0], m[0][0], m[0][0]};
	const Vector4 vec1 = {m[1][1], m[0][1], m[0][1], m[0][1]};
	const Vector4 vec2 = {m[1][2], m[0][2], m[0][2], m[0][2]};
	const Vector4 vec3 = {m[1][3], m[0][3], m[0][3], m[0][3]};

	const Vector4 inv0 = vec1 * fac0 - vec2 * fac1 + vec3 * fac2;
	const Vector4 inv1 = vec0 * fac0 - vec2 * fac3 + vec3 * fac4;
	const Vector4 inv2 = vec0 * fac1 - vec1 * fac3 + vec3 * fac5;
	const Vector4 inv3 = vec0 * fac2 - vec1 * fac4 + vec2 * fac5;

	const Vector4 signA   = {+1, -1, +1, -1};
	const Vector4 signB   = {-1, +1, -1, +1};
	const Matrix4 inverse = {
	    inv0 * signA, inv1 * signB, inv2 * signA, inv3 * signB};

	const Vector4 row0 = {
	    inverse[0][0], inverse[1][0], inverse[2][0], inverse[3][0]};

	const Vector4 dot0 = m[0] * row0;
	const f32 dot1     = (dot0[0] + dot0[1]) + (dot0[2] + dot0[3]);

	const f32 oneOverDeterminant = 1.0f / dot1;

	return inverse * oneOverDeterminant;
}

Matrix4 operator-(const Matrix4& lhs, const Matrix4& rhs)
{

	Matrix4 result;
	for (u8 col = 0; col < 4; col++)
	{
		for (u8 row = 0; row < 4; row++)
		{
			result[col][row] = lhs[col][row] - rhs[col][row];
		}
	}
	return result;
}

Matrix4 operator*(Matrix4 mat, f32 f)
{
	for (int i = 0; i < 4; i++)
	{
		mat[i] *= f;
	}

	return mat;
}

Matrix4 operator/(Matrix4 mat, f32 f)
{

	for (int i = 0; i < 4; i++)
	{
		mat[i] /= f;
	}

	return mat;
}

Matrix4 operator*(const Matrix4& a, const Matrix4& b)
{

	Matrix4 result;
	result[0] =
	    a[0] * b[0][0] + a[1] * b[0][1] + a[2] * b[0][2] + a[3] * b[0][3];
	result[1] =
	    a[0] * b[1][0] + a[1] * b[1][1] + a[2] * b[1][2] + a[3] * b[1][3];
	result[2] =
	    a[0] * b[2][0] + a[1] * b[2][1] + a[2] * b[2][2] + a[3] * b[2][3];
	result[3] =
	    a[0] * b[3][0] + a[1] * b[3][1] + a[2] * b[3][2] + a[3] * b[3][3];
	return result;
}

Vector4 operator*(const Matrix4& a, const Vector4& b)
{

	const Vector4 mul0 = a[0] * b[0];
	const Vector4 mul1 = a[1] * b[1];
	const Vector4 mul2 = a[2] * b[2];
	const Vector4 mul3 = a[3] * b[3];

	const Vector4 add0 = mul0 + mul1;
	const Vector4 add1 = mul2 + mul3;

	return add0 + add1;
}

Vector4 operator*(const Vector4& b, const Matrix4& a) { return a * b; }

} // namespace Teaser