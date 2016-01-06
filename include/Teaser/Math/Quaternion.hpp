//------------------------------------------------------------
// <copyright file="Quaternion.hpp" autor="Markus Perz">
//     Copyright (c) Markus Perz. All rights reserved.
// </copyright>
//------------------------------------------------------------

#ifndef TEASER_MATH_QUATERNION_HPP
#define TEASER_MATH_QUATERNION_HPP

#include <Teaser/Common.hpp>
#include <Teaser/Math/Vector3.hpp>

namespace Teaser
{

// note(markus): Q{s,v} : s = scalar, v = vec3

struct AxisAngle 
{
	Vector3 axis;
	Angle angle;
};

class Quaternion
{
public:
	Quaternion()
	: w(1)
	, v(0) // same as x = y = z = 0
	{
	}

	~Quaternion() {}

	Quaternion(f32 s, f32 x, f32 y, f32 z)
	: s(s)
	, v(x, y, z)
	{
	}

	Quaternion(f32 s, const Vector3& v)
	: s(s)
	, v(v)
	{
	}

	Quaternion(const Quaternion& other)
	: s(other.s)
	, v(other.v)
	{
	}

	union {
		f32 data[4];

		struct
		{
			f32 w, x, y, z;
		};
		struct
		{
			f32 s;
			Vector3 v;
		};
	};

	GLOBAL const Quaternion Identity;

	GLOBAL Quaternion fromAxisAngle(const Angle& angle, const Vector3& axis);
	GLOBAL Quaternion fromTwoVectors(const Vector3& u, const Vector3& v);

	inline f32 lengthSquared() const { return s * s + x * x + y * y + z * z; }
	inline f32 length() const { return sqrt(lengthSquared()); }

	inline Quaternion& normalize()
	{
		float mag2 = lengthSquared();
		if (fabs(mag2) > 0.0001 && fabs(mag2 - 1.0f) > 0.0001) {
			float mag = sqrt(mag2);
			s /= mag;
			v /= mag;
		}
		return *this;
	}

	inline Quaternion getNormalized() const
	{
		Quaternion q = *this; // Calls copy constructor
		return q.normalize();
	}

	Quaternion getConjugate() const;
	Quaternion getInverse() const;
	Quaternion& invert();


	AxisAngle getAxisAngle() const;
	Matrix4 getRotationMatrix()const;

	/*Operators*/
	inline f32 operator[](int index) const { return data[index]; }
	inline f32& operator[](int index) { return data[index]; }

	friend std::ostream& operator<<(std::ostream& stream, const Quaternion& q);

	Quaternion& operator+=(const Quaternion& other);
	Quaternion& operator-=(const Quaternion& other);
	Quaternion& operator*=(f32 scalar);
	Quaternion& operator/=(f32 scalar);
	Quaternion& operator*=(const Quaternion& other);
	bool operator==(const Quaternion& other) const;
	bool operator!=(const Quaternion& other) const;

};

Quaternion operator+(const Quaternion& lhs, const Quaternion& rhs);
Quaternion operator-(const Quaternion& lhs, const Quaternion& rhs);
Quaternion operator*(const Quaternion& lhs, const Quaternion& rhs);

Quaternion operator*(const Quaternion& q, f32 scalar);
Quaternion operator*(f32 scalar, const Quaternion& q);
Quaternion operator/(const Quaternion& q, f32 scalar);
Quaternion operator/(f32 scalar, const Quaternion& q);

Vector3 operator*(const Quaternion& q, const Vector3& vec);
Vector3 operator*(const Vector3& vec, const Quaternion& q);

} // namespace Teaser

#endif // TEASER_MATH_QUATERNION_HPP