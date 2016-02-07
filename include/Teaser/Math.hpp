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
#include <Teaser/Common.hpp>
#include <cmath>

namespace Teaser
{

using Vec2 = Vector2;
using Vec3 = Vector3;
using Vec4 = Vector4;
using Mat4 = Matrix4;

inline double sin(const Angle& a) { return std::sin(a.radians()); }
inline double cos(const Angle& a) { return std::cos(a.radians()); }
inline double tan(const Angle& a) { return std::tan(a.radians()); }

inline double asin(double x) { return std::asin(x); }
inline double acos(double x) { return std::acos(x); }
inline double atan(double x) { return std::atan(x); }

inline double sqrt(double x) { return std::sqrt(x); }
inline float sqrtf(float x) { return std::sqrtf(x); }

inline float sign(float x)
{
	if (x == 0)
		return 1;
	return x / abs(x);
}

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


inline unsigned int round(double x) { return std::round(x); }

inline Angle Degree(float d) { return Angle(d, Angle::Degrees); }

inline Angle Radian(float r) { return Angle(r, Angle::Radians); }

inline float length(const Vector2& vec) { return vec.length(); }

inline float length(const Vector3& vec) { return vec.length(); }

inline float length(const Vector4& vec) { return vec.length(); }

inline Vector2 normalize(const Vector2& vec) { return vec.getNormalized(); }

inline Vector3 normalize(const Vector3& vec) { return vec.getNormalized(); }

inline Vector4 normalize(const Vector4& vec) { return vec.getNormalized(); }

inline Quaternion normalize(const Quaternion& quat) { return quat.getNormalized(); }

inline Matrix4 inverse(const Matrix4& mat) { return mat.getInverse(); }

inline Quaternion inverse(const Quaternion& quat) { return quat.getInverse(); }

inline Quaternion conjugate(const Quaternion& q) { return q.getConjugate(); }

inline Vector3 cross(const Vector3& lhs, const Vector3& rhs)
{
	return lhs.cross(rhs);
}

inline float dot(const Vector2& lhs, const Vector2& rhs) { return lhs.dot(rhs); }

inline float dot(const Vector3& lhs, const Vector3& rhs) { return lhs.dot(rhs); }

inline float dot(const Vector4& lhs, const Vector4& rhs) { return lhs.dot(rhs); }

inline Angle angle(const Vector2& lhs, const Vector2& rhs)
{
	return lhs.angle(rhs);
}

inline Angle angle(const Vector3& lhs, const Vector3& rhs)
{
	return lhs.angle(rhs);
}

Matrix4 translate(float x, float y, float z);

inline Matrix4 translate(const Vector3& t) { return translate(t.x, t.y, t.z); }

Matrix4 scale(float x);

Matrix4 scale(float x, float y, float z);

inline Matrix4 scale(const Vector3& s) { return scale(s.x, s.y, s.z); }

Matrix4 rotate(Angle angle, const Vector3& v);

Matrix4
perspective(float left, float right, float bottom, float top, float near, float far);

Matrix4 perspective(float fovy, float aspect, float zNear, float zFar);

Matrix4 ortho(float left, float right, float bottom, float top);
Matrix4 ortho(float left, float right, float bottom, float top, float near, float far);


Matrix4 lookAt(const Vector3& eye, const Vector3& target, const Vector3& up);

inline Quaternion quatFromAxisAngle(const Angle& angle, const Vector3& axis) { return Quaternion::fromAxisAngle(angle, axis); }
inline Quaternion quatFromTwoVectors(const Vector3& v1, const Vector3& v2) { return Quaternion::fromTwoVectors(v1, v2); }

} // namespace Teaser

#endif // TEASER_MATH_HPP