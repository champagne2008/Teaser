//------------------------------------------------------------
// <copyright file="Vector3.cpp" autor="Markus Perz">
//     Copyright (c) Markus Perz. All rights reserved.
// </copyright>
//------------------------------------------------------------

#include <Teaser/Math/Vector3.hpp>

namespace Teaser
{

const Vector3 Vector3::Zero = Vector3(0, 0, 0);

Vector3 Vector3::cross(const Vector3& other) const
{
	float nx = y * other.z - z * other.y;
	float ny = -x * other.z + z * other.x;
	float nz = x * other.y - y * other.x;

	return Vector3(nx, ny, nz);
}

Angle Vector3::angle(const Vector3& other) const
{
	float angle = acos(dot(other) / (length() * other.length()));
	return Angle(angle, Angle::Radians);
}

bool Vector3::operator==(const Vector3& other) const
{
	for (u8 i = 0; i < 3; i++)
	{
		if (data[i] != other[i])
			return false;
	}
	return true;
}

bool Vector3::operator!=(const Vector3& other) const
{
	return !(*this == other);
}

Vector3& Vector3::operator*=(f32 f)
{
	x *= f;
	y *= f;
	z *= f;

	return *this;
}

Vector3& Vector3::operator/=(f32 f)
{
	x /= f;
	y /= f;
	z /= f;

	return *this;
}

Vector3& Vector3::operator+=(const Vector3& vec)
{
	x += vec.x;
	y += vec.y;
	z += vec.z;

	return *this;
}

Vector3& Vector3::operator-=(const Vector3& vec)
{
	x -= vec.x;
	y -= vec.y;
	z -= vec.z;

	return *this;
}

std::ostream& operator<<(std::ostream& stream, const Vector3& vec)
{
	stream << "Vector3( " << vec.x << ", " << vec.y << ", " << vec.z << ")";
	return stream;
}

Vector3 operator*(const Vector3& vec, f32 f)
{
	return Vector3(vec.x * f, vec.y * f, vec.z * f);
}

Vector3 operator*(f32 f, const Vector3& vec)
{
	return Vector3(vec.x * f, vec.y * f, vec.z * f);
}

Vector3 operator/(const Vector3& vec, f32 f)
{
	return Vector3(vec.x / f, vec.y / f, vec.z / f);
}

Vector3 operator/(f32 f, const Vector3& vec)
{
	return Vector3(vec.x / f, vec.y / f, vec.z / f);
}

Vector3 operator+(const Vector3& lhs, const Vector3& rhs)
{
	return Vector3(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z);
}

Vector3 operator-(const Vector3& lhs, const Vector3& rhs)
{
	return Vector3(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z);
}

// Hadamard Product
Vector3 operator*(const Vector3& a, const Vector3& b)
{
	Vector3 result;
	for (u8 i     = 0; i < 3; i++)
		result[i] = a[i] * b[i];
	return result;
}

// Hadamard Product
Vector3 operator/(const Vector3& a, const Vector3& b)
{
	Vector3 result;
	for (u8 i     = 0; i < 3; i++)
		result[i] = a[i] / b[i];
	return result;
}

} // namespace Teaser