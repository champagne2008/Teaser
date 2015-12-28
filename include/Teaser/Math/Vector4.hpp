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

	inline f32 dot(const Vector4& vec) const
	{
		return x * vec.x + y * vec.y + z * vec.z + w * vec.w;
	}

	/*Operators*/
	f32 operator[](int index) const { return data[index]; }
	f32& operator[](int index) { return data[index]; }

	Vector4& operator*=(f32 f)
	{
		x *= f;
		y *= f;
		z *= f;
		w *= f;

		return *this;
	}

	Vector4& operator/=(f32 f)
	{
		x /= f;
		y /= f;
		z /= f;
		w /= f;

		return *this;
	}

	Vector4& operator+=(const Vector4& vec)
	{
		x += vec.x;
		y += vec.y;
		z += vec.z;
		w += vec.w;

		return *this;
	}

	friend std::ostream& operator<<(std::ostream& stream, const Vector4& vec);
};

std::ostream& operator<<(std::ostream& stream, const Vector4& vec)
{
	stream << "Vector4( " << vec.x << ", " << vec.y << ", " << vec.z << ", "
	       << vec.w << ")" << std::endl;
	return stream;
}

Vector4 operator*(const Vector4& vec, f32 f)
{
	return Vector4(vec.x * f, vec.y * f, vec.z * f, vec.w * f);
}

Vector4 operator*(f32 f, const Vector4& vec)
{
	return Vector4(vec.x * f, vec.y * f, vec.z * f, vec.w * f);
}

Vector4 operator+(const Vector4& lhs, const Vector4& rhs)
{
	return Vector4(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z, lhs.w + rhs.w);
}

Vector4 operator-(const Vector4& lhs, const Vector4& rhs)
{
	return Vector4(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z, lhs.w - rhs.w);

} // namespace Teaser
}
#endif // TEASER_MATH_VECTOR3_HPP