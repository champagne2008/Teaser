//------------------------------------------------------------
// <copyright file="Vector2.hpp" autor="Markus Perz">
//     Copyright (c) Markus Perz. All rights reserved.
// </copyright>
//------------------------------------------------------------

#include <Teaser/Math/Vector2.hpp>

namespace Teaser
{

const Vector2 Vector2::Zero = Vector2(0,0);

Angle Vector2::angle(const Vector2& other) const
{
	float angle = acos(dot(other) / (length() * other.length()));
	return Angle(angle, Angle::Radians);
}

Vector2& Vector2::operator*=(f32 f)
{
	x *= f;
	y *= f;

	return *this;
}

Vector2& Vector2::operator/=(f32 f)
{
	x /= f;
	y /= f;

	return *this;
}

Vector2& Vector2::operator+=(const Vector2& vec)
{
	x += vec.x;
	y += vec.y;

	return *this;
}

std::ostream& operator<<(std::ostream& stream, const Vector2& vec)
{
	stream << "Vector2( " << vec.x << ", " << vec.y << ")" << std::endl;
	return stream;
}

bool Vector2::operator==(const Vector2& other) const
{
	for (u8 i = 0; i < 2; i++)
	{
		if (data[i] != other[i])
			return false;
	}
	return true;
}

bool Vector2::operator !=(const Vector2& other) const
{
	return !(*this == other);
}

Vector2 operator*(const Vector2& vec, f32 f)
{
	return Vector2(vec.x * f, vec.y * f);
}

Vector2 operator*(f32 f, const Vector2& vec)
{
	return Vector2(vec.x * f, vec.y * f);
}

Vector2 operator/(const Vector2& vec, f32 f)
{
	return Vector2(vec.x / f, vec.y / f);
}

Vector2 operator/(f32 f, const Vector2& vec)
{
	return Vector2(vec.x / f, vec.y / f);
}

Vector2 operator+(const Vector2& lhs, const Vector2& rhs)
{
	return Vector2(lhs.x + rhs.x, lhs.y + rhs.y);
}

Vector2 operator-(const Vector2& lhs, const Vector2& rhs)
{
	return Vector2(lhs.x - rhs.x, lhs.y - rhs.y);
}

// Hadamard Product
Vector2 operator*(const Vector2& a, const Vector2& b)
{
	Vector2 result;
	for (u8 i = 0; i < 2; i++)
		result[i] = a[i] * b[i];
	return result;
}

// Hadamard Product
Vector2 operator/(const Vector2& a, const Vector2& b)
{
	Vector2 result;
	for (u8 i = 0; i < 2; i++)
		result[i] = a[i] / b[i];
	return result;
}

} // namespace Teaser