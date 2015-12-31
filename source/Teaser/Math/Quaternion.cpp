//------------------------------------------------------------
// <copyright file="Quaternion.cpp" autor="Markus Perz">
//     Copyright (c) Markus Perz. All rights reserved.
// </copyright>
//------------------------------------------------------------

#include <Teaser/Math/Quaternion.hpp>
#include <Teaser/Math.hpp>

namespace Teaser
{
	const Quaternion Quaternion::Identity = Quaternion(1, Vector3::Zero); // s = 1, v = ( 0, 0, 0);

	Quaternion Quaternion::fromAxisAngle(const Angle& angle, const Vector3& axis)
	{
		float a = angle.radians();
		float half_sin = sin(0.5f * a);
		float half_cos = cos(0.5f * a);
		return Quaternion(half_cos, half_sin * axis);
	}

	Quaternion Quaternion::fromTwoVectors(const Vector3& u, const Vector3& v)
	{
		float cos_theta = dot(normalize(u), normalize(v));
		float angle = acos(cos_theta);
		Vector3 w = normalize(cross(u, v));
		return fromAxisAngle(angle, w);
	}


} // namespace Teaser