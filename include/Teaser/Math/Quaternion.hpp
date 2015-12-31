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
class Quaternion
{
public:
	Quaternion()
	: w(1)
	, v(0) // same as x = y = z = 0
	{
	}

	~Quaternion() {}

	Quaternion(f32 scalar, f32 x, f32 y, f32 z)
	: s(s)
	, v(x, y, z)
	{
	}

	Quaternion(f32 scalar, const Vector3& vector)
	: s(s)
	, v(v)
	{
	}

	Quaternion(const Quaternion& other) : s(other.s), v(other.v)
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
};

} // namespace Teaser

#endif // TEASER_MATH_QUATERNION_HPP