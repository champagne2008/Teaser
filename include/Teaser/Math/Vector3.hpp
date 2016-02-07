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

	static const Vector3 Zero;

	Vector3()
	: x(0)
	, y(0)
	, z(0)
	{
	}

	explicit Vector3(float xyz)
	: x(xyz)
	, y(xyz)
	, z(xyz)
	{
	}

	Vector3(float x, float y, float z)
	: x(x)
	, y(y)
	, z(z)
	{
	}

	~Vector3() {}

	Vector3(const Vector3& other) = default;

	union {
		float data[3];
		struct
		{
			float x, y, z;
		};
		struct
		{
			float r, g, b;
		};
	};

	inline float lenthSquared() const { return x * x + y * y + z * z; }

	inline float length() const { return sqrtf(lenthSquared()); }

	inline Vector3& normalize()
	{
		float l = length();
		x /= l;
		y /= l;
		z /= l;
		return *this;
	}

	inline Vector3 getNormalized() const
	{
		Vector3 v = *this;
		return v.normalize();
	}


	inline float dot(const Vector3& vec) const
	{
		return x * vec.x + y * vec.y + z * vec.z;
	}

	Vector3 cross(const Vector3& other) const;
	Angle angle(const Vector3& other) const;

	std::string toString() const;

	/* Operators */
	inline float operator[](int index) const { return data[index]; }
	inline float& operator[](int index) { return data[index]; }

	bool operator ==(const Vector3& other) const;
	bool operator !=(const Vector3& other) const;

	inline Vector3 operator-() const { return Vector3(-x, -y, -z); }

	Vector3& operator*=(float f);

	Vector3& operator/=(float f);

	Vector3& operator+=(const Vector3& vec);

	Vector3& operator-=(const Vector3& vec);


	friend std::ostream& operator<<(std::ostream& stream, const Vector3& vec);
};

std::ostream& operator<<(std::ostream& stream, const Vector3& vec);

Vector3 operator*(const Vector3& vec, float f);

Vector3 operator*(float f, const Vector3& vec);

Vector3 operator/(const Vector3& vec, float f);

Vector3 operator/(float f, const Vector3& vec);

Vector3 operator+(const Vector3& lhs, const Vector3& rhs);

Vector3 operator-(const Vector3& lhs, const Vector3& rhs);

Vector3 operator*(const Vector3& a, const Vector3& b);

Vector3 operator/(const Vector3& a, const Vector3& b);

} // namespace Teaser

#endif // TEASER_MATH_VECTOR3_HPP