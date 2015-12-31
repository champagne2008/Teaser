//------------------------------------------------------------
// <copyright file="Vector2.hpp" autor="Markus Perz">
//     Copyright (c) Markus Perz. All rights reserved.
// </copyright>
//------------------------------------------------------------

#ifndef TEASER_MATH_VECTOR2_HPP
#define TEASER_MATH_VECTOR2_HPP

#include <Teaser/Common.hpp>
#include <Teaser/Math/Angle.hpp>

namespace Teaser
{
class Vector2
{
public:

	GLOBAL const Vector2 Zero;

	Vector2()
	: x(0)
	, y(0)
	{
	}

	explicit Vector2(f32 xy)
	: x(xy)
	, y(xy)
	{
	}

	Vector2(f32 x, f32 y)
	: x(x)
	, y(y)
	{
	}

	~Vector2() {}

	Vector2(const Vector2& other) = default;


	union {
		f32 data[2];
		struct
		{
			f32 x, y;
		};
		struct
		{
			f32 r, g;
		};
		struct
		{
			f32 u, v;
		};
	};

	inline f32 lenthSquared() const { return x * x + y * y; }

	inline f32 length() const { return sqrtf(lenthSquared()); }

	inline void normalize()
	{
		f32 l = length();
		x /= l;
		y /= l;
	}

	inline Vector2 getNormalized() const
	{
		Vector2 v = *this;
		v.normalize();
		return v;
	}

	inline f32 dot(const Vector2& vec) const { return x * vec.x + y * vec.y; }

	Angle angle(const Vector2& other) const;

	/*Operators*/

	bool operator ==(const Vector2& other) const;
	bool operator !=(const Vector2& other) const;

	Vector2& operator*=(f32 f);

	Vector2& operator/=(f32 f);

	Vector2& operator+=(const Vector2& vec);

	inline f32 operator[](int index) const { return data[index]; }
	inline f32& operator[](int index) { return data[index]; }

	friend std::ostream& operator<<(std::ostream& stream, const Vector2& vec);
};

std::ostream& operator<<(std::ostream& stream, const Vector2& vec);

Vector2 operator*(const Vector2& vec, f32 f);
Vector2 operator*(f32 f, const Vector2& vec);

Vector2 operator/(const Vector2& vec, f32 f);

Vector2 operator/(f32 f, const Vector2& vec);

Vector2 operator+(const Vector2& lhs, const Vector2& rhs);

Vector2 operator-(const Vector2& lhs, const Vector2& rhs);

Vector2 operator*(const Vector2& a, const Vector2& b);

Vector2 operator/(const Vector2& a, const Vector2& b);

} // Teaser

#endif // TEASER_MATH_VECTOR2_HPP