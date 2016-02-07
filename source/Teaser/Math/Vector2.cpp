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

std::string Vector2::toString() const
{
	return std::string("Vector2( " + std::to_string(x) + ", " + std::to_string(y) + ")");
}

Vector2& Vector2::operator*=(float f)
{
	x *= f;
	y *= f;

	return *this;
}

Vector2& Vector2::operator/=(float f)
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

Vector2& Vector2::operator-=(const Vector2& vec)
{
	x -= vec.x;
	y -= vec.y;

	return *this;
}

std::ostream& operator<<(std::ostream& stream, const Vector2& vec)
{
	stream << vec.toString();
	return stream;
}

bool Vector2::operator==(const Vector2& other) const
{
	for (unsigned int i = 0; i < 2; i++)
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

Vector2 operator*(const Vector2& vec, float f)
{
	return Vector2(vec.x * f, vec.y * f);
}

Vector2 operator*(float f, const Vector2& vec)
{
	return Vector2(vec.x * f, vec.y * f);
}

Vector2 operator/(const Vector2& vec, float f)
{
	return Vector2(vec.x / f, vec.y / f);
}

Vector2 operator/(float f, const Vector2& vec)
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
	for (unsigned int i = 0; i < 2; i++)
		result[i] = a[i] * b[i];
	return result;
}

// Hadamard Product
Vector2 operator/(const Vector2& a, const Vector2& b)
{
	Vector2 result;
	for (unsigned int i = 0; i < 2; i++)
		result[i] = a[i] / b[i];
	return result;
}

} // namespace Teaser