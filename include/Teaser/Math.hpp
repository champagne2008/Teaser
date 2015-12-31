//------------------------------------------------------------
// <copyright file="Math.hpp" autor="Markus Perz">
//     Copyright (c) Markus Perz. All rights reserved.
// </copyright>
//------------------------------------------------------------

#ifndef TEASER_MATH_HPP
#define TEASER_MATH_HPP

#include <Teaser/Math/Angle.hpp>
#include <Teaser/Math/Matrix4.hpp>
#include <Teaser/Math/Quaternion.hpp>
#include <Teaser/Math/Vector2.hpp>
#include <Teaser/Math/Vector3.hpp>
#include <Teaser/Math/Vector4.hpp>

#include <cmath>

namespace Teaser
{

inline f64 sin(const Angle& a) { return std::sin(a.radians()); }
inline f64 cos(const Angle& a) { return std::cos(a.radians()); }
inline f64 tan(const Angle& a) { return std::tan(a.radians()); }

inline f64 asin(f64 x) { return std::asin(x); }
inline f64 acos(f64 x) { return std::acos(x); }
inline f64 atan(f64 x) { return std::atan(x); }

inline f64 sqrt(f64 x) { return std::sqrt(x); }
inline f32 sqrtf(f32 x) { return std::sqrtf(x); }

template <typename T>
inline T min(const T& a, const T& b)
{
	return (a < b) ? a : b;
}

template <typename T>
inline T max(const T& a, const T& b)
{
	return (a > b) ? a : b;
}

template <typename T>
inline T clamp(const T& lowerbound, const T& upperbound, const T& value)
{
	return min(max(value, lowerbound), upperbound);
}

template <typename T>
inline T lerp(const T& a, const T& b, float clamped01) 
{
	clamped01 = min(max(clamped01,0.0f), 1.0f);
	return a + clamped01*(b - a);
}

inline Angle Degree(f32 d) { return Angle(d, Angle::Degrees); }

inline Angle Radian(f32 r) { return Angle(r, Angle::Radians); }

inline f32 length(const Vector2& vec) { return vec.length(); }

inline f32 length(const Vector3& vec) { return vec.length(); }

inline f32 length(const Vector4& vec) { return vec.length(); }

inline Vector2 normalize(const Vector2& vec) { return vec.getNormalized(); }

inline Vector3 normalize(const Vector3& vec) { return vec.getNormalized(); }

inline Vector4 normalize(const Vector4& vec) { return vec.getNormalized(); }

inline Matrix4 inverse(const Matrix4& mat) { return mat.getInverse(); }

inline Vector3 cross(const Vector3& lhs, const Vector3& rhs)
{
	return lhs.cross(rhs);
}

inline f32 dot(const Vector2& lhs, const Vector2& rhs) { return lhs.dot(rhs); }

inline f32 dot(const Vector3& lhs, const Vector3& rhs) { return lhs.dot(rhs); }

inline f32 dot(const Vector4& lhs, const Vector4& rhs) { return lhs.dot(rhs); }

inline Angle angle(const Vector2& lhs, const Vector2& rhs)
{
	return lhs.angle(rhs);
}

inline Angle angle(const Vector3& lhs, const Vector3& rhs)
{
	return lhs.angle(rhs);
}

Matrix4 translate(f32 x, f32 y, f32 z);

inline Matrix4 translate(Vector3 t) { return translate(t.x, t.y, t.z); }

Matrix4 scale(f32 x);

Matrix4 scale(f32 x, f32 y, f32 z);

inline Matrix4 scale(Vector3 s) { return scale(s.x, s.y, s.z); }

Matrix4 rotate(Angle angle, const Vector3& v);

Matrix4
perspective(f32 left, f32 right, f32 bottom, f32 top, f32 near, f32 far);

Matrix4 perspective(f32 fovy, f32 aspect, f32 zNear, f32 zFar);

Matrix4 ortho(f32 left, f32 right, f32 bottom, f32 top, f32 near, f32 far);

inline Quaternion quatFromAxisAngle(const Angle& angle, const Vector3& axis) { return Quaternion::fromAxisAngle(angle, axis); }

} // namespace Teaser

#endif // TEASER_MATH_HPP