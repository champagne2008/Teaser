//------------------------------------------------------------
// <copyright file="Matrix4.cpp" autor="Markus Perz">
//     Copyright (c) Markus Perz. All rights reserved.
// </copyright>
//------------------------------------------------------------

#include <Teaser/Math/Matrix4.hpp>

namespace Teaser
{

Matrix4& Matrix4::operator*=(f32 f)
{
	for (int i = 0; i < 4; i++)
	{
		data[i] *= f;
	}
	return *this;
}

Matrix4& Matrix4::operator/=(f32 f)
{
	for (int i = 0; i < 4; i++)
	{
		data[i] /= f;
	}
	return *this;
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

Matrix4 operator *(const Matrix4 & lhs, const Matrix4& rhs) 
{
	Matrix4 r;

	for (int row = 0; row < 4; row++) 
	{
		for (int i = 0; i < 4; i++)
		{
			r[row][i] = lhs[row].dot(Vector4(rhs[i]));
		}
	}
	return r;
}

} // namespace Teaser