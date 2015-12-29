//------------------------------------------------------------
// <copyright file="Vector2.hpp" autor="Markus Perz">
//     Copyright (c) Markus Perz. All rights reserved.
// </copyright>
//------------------------------------------------------------

#include <Teaser/Math/Vector2.hpp>

namespace Teaser
{

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

} // namespace Teaser