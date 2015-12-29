//------------------------------------------------------------
// <copyright file="Math.cpp" autor="Markus Perz">
//     Copyright (c) Markus Perz. All rights reserved.
// </copyright>
//------------------------------------------------------------

#include <Teaser/Math.hpp>

namespace Teaser
{
namespace Math
{

Matrix4 translate(f32 x, f32 y, f32 z)
{
	Matrix4 m;
	m[3] = Vector4(x, y, z, 1);
	return m;
}

Matrix4 scale(f32 x, f32 y, f32 z)
{
	Matrix4 m;
	m[0][0] = x;
	m[1][1] = y;
	m[2][2] = z;
	return m;
}

Matrix4 rotateZ(Angle angle)
{
	Matrix4 m;
	m[0][0] = cos(angle.radians());
	m[1][0] = sin(angle.radians());
	m[0][1] = -sin(angle.radians());
	m[1][1] = cos(angle.radians());

	return m;
}
} // namespace Math
} // namespace Teaser