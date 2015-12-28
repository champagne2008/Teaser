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

} // namespace Math

} // namespace Teaser

#endif // TEASER_MATH_HPP