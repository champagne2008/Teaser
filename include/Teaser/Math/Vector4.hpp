//------------------------------------------------------------
// <copyright file="Vector4.hpp" autor="Markus Perz">
//     Copyright (c) Markus Perz. All rights reserved.
// </copyright>
//------------------------------------------------------------

#ifndef TEASER_MATH_VECTOR4_HPP
#define TEASER_MATH_VECTOR4_HPP

#include <Teaser/Common.hpp>
#include <Teaser/Math/Vector3.hpp>
#include <iostream>

namespace Teaser
{

class Vector3;

class Vector4
{
public:
	static const Vector4 Zero;

	Vector4()
	: x(0)
	, y(0)
	, z(0)
	, w(0)
	{
	}

	explicit Vector4(float xyzw)
	: x(xyzw)
	, y(xyzw)
	, z(xyzw)
	, w(xyzw)
	{
	}

	Vector4(float x, float y, float z, float w)
	: x(x)
	, y(y)
	, z(z)
	, w(w)
	{
	}

	Vector4(const Vector3& xyz, float w)
		: x(xyz.x)
		, y(xyz.y)
		, z(xyz.z)
		, w(w)
	{
	}
	Vector4(const Vector4& other) = default;

	~Vector4() {}

	union {
		float data[4];
		struct
		{
			float x, y, z, w;
		};


		struct
		{
			float r, g, b, a;
		};
	};

	inline float lenthSquared() const { return x * x + y * y + z * z + w * w; }

	inline float length() const { return sqrtf(lenthSquared()); }

	inline Vector4& normalize()
	{
		float l = length();
		x /= l;
		y /= l;
		z /= l;
		w /= l;

		return *this;
	}

	inline Vector4 getNormalized() const
	{
		Vector4 v = *this;
		return v.normalize();
	}

	inline float dot(const Vector4& vec) const
	{
		return x * vec.x + y * vec.y + z * vec.z + w * vec.w;
	}

	std::string Vector4::toString() const;

	inline Vector4 operator-() const { return Vector4(-x, -y, -z, -w); }

	bool operator==(const Vector4& other) const;
	bool operator!=(const Vector4& other) const;

	/*Operators*/
	inline float operator[](int index) const { return data[index]; }
	inline float& operator[](int index) { return data[index]; }

	Vector4& operator*=(float f);

	Vector4& operator/=(float f);

	Vector4& operator+=(const Vector4& vec);

	Vector4& operator-=(const Vector4& vec);

	friend std::ostream& operator<<(std::ostream& stream, const Vector4& vec);
};

std::ostream& operator<<(std::ostream& stream, const Vector4& vec);

Vector4 operator*(const Vector4& vec, float f);

Vector4 operator*(float f, const Vector4& vec);

Vector4 operator/(const Vector4& vec, float f);

Vector4 operator/(float f, const Vector4& vec);

Vector4 operator+(const Vector4& lhs, const Vector4& rhs);

Vector4 operator-(const Vector4& lhs, const Vector4& rhs);

Vector4 operator*(const Vector4& a, const Vector4& b);

Vector4 operator/(const Vector4& a, const Vector4& b);

} // namespace Teaser
#endif // TEASER_MATH_VECTOR3_HPP