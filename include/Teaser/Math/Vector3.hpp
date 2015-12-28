//------------------------------------------------------------
// <copyright file="Vector3.hpp" autor="Markus Perz">
//     Copyright (c) Markus Perz. All rights reserved.
// </copyright>
//------------------------------------------------------------

#ifndef TEASER_MATH_VECTOR3_HPP
#define TEASER_MATH_VECTOR3_HPP

#include <Teaser/Common.hpp>
#include <Teaser/Math/Angle.hpp>

namespace Teaser
{
class Vector3
{
public:
	Vector3()
	: x(0)
	, y(0)
	, z(0)
	{
	}

	explicit Vector3(f32 xyz)
	: x(xyz)
	, y(xyz)
	, z(xyz)
	{
	}

	Vector3(f32 x, f32 y, f32 z)
	: x(x)
	, y(y)
	, z(z)
	{
	}

	~Vector3() {}

	union {
		f32 data[3];
		struct
		{
			f32 x, y, z;
		};
		struct
		{
			f32 r, g, b;
		};
	};

	inline f32 lenthSquared() const { return x * x + y * y + z * z; }

	inline f32 length() const { return sqrtf(lenthSquared()); }

	inline void normalize()
	{
		f32 l = length();
		x /= l;
		y /= l;
		z /= l;
	}

	inline f32 dot(const Vector3& vec) const
	{
		return x * vec.x + y * vec.y + z * vec.z;
	}

	Vector3 cross(const Vector3& other) const
	{
		float nx = y * other.z - z * other.y;
		float ny = -x * other.z + z * other.x;
		float nz = x * other.y - y * other.x;

		return Vector3(nx, ny, nz);
	}

	Angle angle(const Vector3& other) const
	{
		float angle = acos(dot(other) / (length() * other.length()));
		return Angle(angle, Angle::Radians);
	}

	/* Operators */
	f32 operator[](int index) const { return data[index]; }
	f32& operator[](int index) { return data[index]; }

	Vector3& operator*=(f32 f)
	{
		x *= f;
		y *= f;
		z *= f;

		return *this;
	}

	Vector3& operator/=(f32 f)
	{
		x /= f;
		y /= f;
		z /= f;

		return *this;
	}

	Vector3& operator+=(const Vector3& vec)
	{
		x += vec.x;
		y += vec.y;
		z += vec.z;

		return *this;
	}

	friend std::ostream& operator<<(std::ostream& stream, const Vector3& vec);
};

std::ostream& operator<<(std::ostream& stream, const Vector3& vec)
{
	stream << "Vector3( " << vec.x << ", " << vec.y << ", " << vec.z << ")"
	       << std::endl;
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

Vector3 operator+(const Vector3& lhs, const Vector3& rhs)
{
	return Vector3(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z);
}

Vector3 operator-(const Vector3& lhs, const Vector3& rhs)
{
	return Vector3(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z);
}

} // namespace Teaser

#endif // TEASER_MATH_VECTOR3_HPP