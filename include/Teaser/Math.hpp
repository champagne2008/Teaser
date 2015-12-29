//------------------------------------------------------------
// <copyright file="Math.hpp" autor="Markus Perz">
//     Copyright (c) Markus Perz. All rights reserved.
// </copyright>
//------------------------------------------------------------

#ifndef TEASER_MATH_HPP
#define TEASER_MATH_HPP

#include <Teaser/Math/Angle.hpp>
#include <Teaser/Math/Matrix4.hpp>
#include <Teaser/Math/Vector2.hpp>
#include <Teaser/Math/Vector3.hpp>
#include <Teaser/Math/Vector4.hpp>

#include <cmath>

namespace Teaser
{

namespace Math
{

inline f32 getLength(Vector2 vec) { return vec.length(); }

inline f32 getLength(Vector3 vec) { return vec.length(); }

inline f32 getLength(Vector4 vec) { return vec.length(); }

Vector3 cross(const Vector3& lhs, const Vector3& rhs) { return lhs.cross(rhs); }

inline f32 dot(const Vector2& lhs, const Vector2& rhs) { return lhs.dot(rhs); }

inline f32 dot(const Vector3& lhs, const Vector3& rhs) { return lhs.dot(rhs); }

inline f32 dot(const Vector4& lhs, const Vector4& rhs) { return lhs.dot(rhs); }

inline Angle getAngleBetween(const Vector2& lhs, const Vector2& rhs)
{
	return lhs.angle(rhs);
}

inline Angle getAngleBetween(const Vector3& lhs, const Vector3& rhs)
{
	return lhs.angle(rhs);
}

Matrix4 translate(f32 x, f32 y, f32 z)
{
	Matrix4 m;
	m[3] = Vector4(x, y, z, 1);
	return m;
}

Matrix4 scale(f32 x, f32 y, f32 z)
{
	Matrix4 m;
	m[0][0] = x;
	m[1][1] = y;
	m[2][2] = z;
	return m;
}

Matrix4 rotateZ(Angle angle)
{
	Matrix4 m;
	m[0][0] = cos(angle.radians());
	m[1][0] = sin(angle.radians());
	m[0][1] = -sin(angle.radians());
	m[1][1] = cos(angle.radians());

	return m;
}

} // namespace Math

} // namespace Teaser

#endif // TEASER_MATH_HPP