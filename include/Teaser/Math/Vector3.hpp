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

	GLOBAL const Vector3 Zero;

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

	Vector3(const Vector3& other) = default;


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

	inline Vector3 getNormalized() const
	{
		Vector3 v = *this;
		v.normalize();
		return v;
	}


	inline f32 dot(const Vector3& vec) const
	{
		return x * vec.x + y * vec.y + z * vec.z;
	}

	Vector3 cross(const Vector3& other) const;
	Angle angle(const Vector3& other) const;

	/* Operators */
	inline f32 operator[](int index) const { return data[index]; }
	inline f32& operator[](int index) { return data[index]; }

	bool operator ==(const Vector3& other) const;
	bool operator !=(const Vector3& other) const;

	inline Vector3 operator-() const { return Vector3(-x, -y, -z); }

	Vector3& operator*=(f32 f);

	Vector3& operator/=(f32 f);

	Vector3& operator+=(const Vector3& vec);

	friend std::ostream& operator<<(std::ostream& stream, const Vector3& vec);
};

std::ostream& operator<<(std::ostream& stream, const Vector3& vec);

Vector3 operator*(const Vector3& vec, f32 f);

Vector3 operator*(f32 f, const Vector3& vec);

Vector3 operator/(const Vector3& vec, f32 f);

Vector3 operator/(f32 f, const Vector3& vec);

Vector3 operator+(const Vector3& lhs, const Vector3& rhs);

Vector3 operator-(const Vector3& lhs, const Vector3& rhs);

Vector3 operator*(const Vector3& a, const Vector3& b);

Vector3 operator/(const Vector3& a, const Vector3& b);

} // namespace Teaser

#endif // TEASER_MATH_VECTOR3_HPP