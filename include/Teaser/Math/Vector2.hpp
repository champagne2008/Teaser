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

	static const Vector2 Zero;

	Vector2()
	: x(0)
	, y(0)
	{
	}

	explicit Vector2(float xy)
	: x(xy)
	, y(xy)
	{
	}

	Vector2(float x, float y)
	: x(x)
	, y(y)
	{
	}

	~Vector2() {}

	Vector2(const Vector2& other) = default;


	union {
		float data[2];
		struct
		{
			float x, y;
		};
		struct
		{
			float r, g;
		};
		struct
		{
			float u, v;
		};
	};

	inline float lenthSquared() const { return x * x + y * y; }

	inline float length() const { return sqrtf(lenthSquared()); }

	inline Vector2& normalize()
	{
		float l = length();
		x /= l;
		y /= l;
		return *this;
	}

	inline Vector2 getNormalized() const
	{
		Vector2 v = *this;
		return v.normalize();
	}

	inline float dot(const Vector2& vec) const { return x * vec.x + y * vec.y; }

	Angle angle(const Vector2& other) const;

	std::string toString() const;

	/*Operators*/

	bool operator ==(const Vector2& other) const;
	bool operator !=(const Vector2& other) const;

	inline Vector2 operator-() const  { return Vector2(-x, -y); }

	Vector2& operator*=(float f);

	Vector2& operator/=(float f);

	Vector2& operator+=(const Vector2& vec);

	Vector2& operator-=(const Vector2& vec);

	inline float operator[](int index) const { return data[index]; }
	inline float& operator[](int index) { return data[index]; }

	friend std::ostream& operator<<(std::ostream& stream, const Vector2& vec);

};

std::ostream& operator<<(std::ostream& stream, const Vector2& vec);

Vector2 operator*(const Vector2& vec, float f);
Vector2 operator*(float f, const Vector2& vec);

Vector2 operator/(const Vector2& vec, float f);

Vector2 operator/(float f, const Vector2& vec);

Vector2 operator+(const Vector2& lhs, const Vector2& rhs);

Vector2 operator-(const Vector2& lhs, const Vector2& rhs);

Vector2 operator*(const Vector2& a, const Vector2& b);

Vector2 operator/(const Vector2& a, const Vector2& b);

} // Teaser

#endif // TEASER_MATH_VECTOR2_HPP