//------------------------------------------------------------
// <copyright file="Vector4.hpp" autor="Markus Perz">
//     Copyright (c) Markus Perz. All rights reserved.
// </copyright>
//------------------------------------------------------------

#ifndef TEASER_MATH_VECTOR4_HPP
#define TEASER_MATH_VECTOR4_HPP

#include <Teaser/Common.hpp>

#include <iostream>

namespace Teaser
{
class Vector4
{
public:

	GLOBAL const Vector4 Zero;

	Vector4()
	: x(0)
	, y(0)
	, z(0)
	, w(0)
	{
	}

	explicit Vector4(f32 xyzw)
	: x(xyzw)
	, y(xyzw)
	, z(xyzw)
	, w(xyzw)
	{
	}

	Vector4(f32 x, f32 y, f32 z, f32 w)
	: x(x)
	, y(y)
	, z(z)
	, w(w)
	{
	}

	Vector4(const Vector4& other) = default;

	~Vector4() {}

	union {
		f32 data[4];
		struct
		{
			f32 x, y, z, w;
		};
		struct
		{
			f32 r, g, b, a;
		};
	};

	inline f32 lenthSquared() const { return x * x + y * y + z * z + w * w; }

	inline f32 length() const { return sqrtf(lenthSquared()); }

	inline void normalize()
	{
		f32 l = length();
		x /= l;
		y /= l;
		z /= l;
		w /= l;
	}

	inline Vector4 getNormalized() const
	{
		Vector4 v = *this;
		v.normalize();
		return v;
	}

	inline f32 dot(const Vector4& vec) const
	{
		return x * vec.x + y * vec.y + z * vec.z + w * vec.w;
	}

	bool operator ==(const Vector4& other) const;
	bool operator !=(const Vector4& other) const;

	/*Operators*/
	inline f32 operator[](int index) const { return data[index]; }
	inline f32& operator[](int index) { return data[index]; }

	Vector4& operator*=(f32 f);

	Vector4& operator/=(f32 f);

	Vector4& operator+=(const Vector4& vec);

	friend std::ostream& operator<<(std::ostream& stream, const Vector4& vec);
};

std::ostream& operator<<(std::ostream& stream, const Vector4& vec);

Vector4 operator*(const Vector4& vec, f32 f);

Vector4 operator*(f32 f, const Vector4& vec);

Vector4 operator/(const Vector4& vec, f32 f);

Vector4 operator/(f32 f, const Vector4& vec);

Vector4 operator+(const Vector4& lhs, const Vector4& rhs);

Vector4 operator-(const Vector4& lhs, const Vector4& rhs);

Vector4 operator*(const Vector4& a, const Vector4& b);

Vector4 operator/(const Vector4& a, const Vector4& b);

} // namespace Teaser
#endif // TEASER_MATH_VECTOR3_HPP