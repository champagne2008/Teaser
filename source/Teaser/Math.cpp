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

Matrix4 scale(f32 x) { return scale(x, x, x); }

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

Matrix4 perspective(f32 left, f32 right, f32 bottom, f32 top, f32 near, f32 far) 
{
	Matrix4 m;
	m.col0.x = 2*near / (right - left);
	m.col1.y = 2*near / (top - bottom);
	m.col2 = Vector4((right + left) / (right - left), (top + bottom) / (top - bottom), -(far + near) / (far - near), -1);
	m.col3 = Vector4(0, 0, -2 * far*near / (far - near), 0);
	return m;
}

Matrix4 ortho(f32 left, f32 right, f32 bottom, f32 top, f32 near, f32 far)
{
	Matrix4 m;
	m.col0.x = 2 / (right - left);
	m.col1.y = 2 / (top - bottom);
	m.col2.z = -2 / (far - near);
	m.col3 = Vector4(-(right + left) / (right - left), -(top + bottom) / (top-bottom), -(far + near) / (far - near), 1);
	return m;
}

} // namespace Math
} // namespace Teaser