//------------------------------------------------------------
// <copyright file="Vector4.cpp" autor="Markus Perz">
//     Copyright (c) Markus Perz. All rights reserved.
// </copyright>
//------------------------------------------------------------

#include <Teaser/Math/Vector4.hpp>

namespace Teaser
{

Vector4& Vector4::operator*=(f32 f)
{
	x *= f;
	y *= f;
	z *= f;
	w *= f;

	return *this;
}

Vector4& Vector4::operator/=(f32 f)
{
	x /= f;
	y /= f;
	z /= f;
	w /= f;

	return *this;
}

Vector4& Vector4::operator+=(const Vector4& vec)
{
	x += vec.x;
	y += vec.y;
	z += vec.z;
	w += vec.w;

	return *this;
}

std::ostream& operator<<(std::ostream& stream, const Vector4& vec)
{
	stream << "Vector4( " << vec.x << ", " << vec.y << ", " << vec.z << ", "
	       << vec.w << ")" << std::endl;
	return stream;
}

Vector4 operator*(const Vector4& vec, f32 f)
{
	return Vector4(vec.x * f, vec.y * f, vec.z * f, vec.w * f);
}

Vector4 operator*(f32 f, const Vector4& vec)
{
	return Vector4(vec.x * f, vec.y * f, vec.z * f, vec.w * f);
}

Vector4 operator/(const Vector4& vec, f32 f)
{
	return Vector4(vec.x / f, vec.y / f, vec.z / f, vec.w / f);
}

Vector4 operator/(f32 f, const Vector4& vec)
{
	return Vector4(vec.x / f, vec.y / f, vec.z / f, vec.w / f);
}

Vector4 operator+(const Vector4& lhs, const Vector4& rhs)
{
	return Vector4(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z, lhs.w + rhs.w);
}

Vector4 operator-(const Vector4& lhs, const Vector4& rhs)
{
	return Vector4(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z, lhs.w - rhs.w);
} 
} // namespace Teaser