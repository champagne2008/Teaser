//------------------------------------------------------------
// <copyright file="Math.cpp" autor="Markus Perz">
//     Copyright (c) Markus Perz. All rights reserved.
// </copyright>
//------------------------------------------------------------

#include <Teaser/Math.hpp>

namespace Teaser
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

Matrix4 rotate(Angle angle, const Vector3& v)
{
	const f32 c = cos(angle.radians());
	const f32 s = sin(angle.radians());

	Vector3 axis = v;
	axis.normalize();
	const Vector3 t = (1.0f - c) * axis;

	Matrix4 rot;

	rot[0][0] = c + t.x * axis.x;
	rot[0][1] = 0 + t.x * axis.y + s * axis.z;
	rot[0][2] = 0 + t.x * axis.z - s * axis.y;
	rot[0][3] = 0;

	rot[1][0] = 0 + t.y * axis.x - s * axis.z;
	rot[1][1] = c + t.y * axis.y;
	rot[1][2] = 0 + t.y * axis.z + s * axis.x;
	rot[1][3] = 0;

	rot[2][0] = 0 + t.z * axis.x + s * axis.y;
	rot[2][1] = 0 + t.z * axis.y - s * axis.x;
	rot[2][2] = c + t.z * axis.z;
	rot[2][3] = 0;

	return rot;
}

Matrix4 perspective(f32 left, f32 right, f32 bottom, f32 top, f32 near, f32 far)
{
	Matrix4 m;
	m.col0.x = 2 * near / (right - left);
	m.col1.y = 2 * near / (top - bottom);
	m.col2   = Vector4(0, 0, (far + near) / (far - near), -1);
	m.col3   = Vector4(0, 0, -2 * far * near / (far - near), 0);
	return m;
}

Matrix4 perspective(f32 fovy, f32 aspect, f32 zNear, f32 zFar)
{

	const f32 tanHalfFovy = tan(0.5f * fovy);

	Matrix4 result = {};
	result[0][0]   = 1.0f / (aspect * tanHalfFovy);
	result[1][1]   = 1.0f / (tanHalfFovy);
	result[2][2]   = -(zFar + zNear) / (zFar - zNear);
	result[2][3]   = -1.0f;
	result[3][2]   = -2.0f * zFar * zNear / (zFar - zNear);

	return result;
}

Matrix4 ortho(f32 left, f32 right, f32 bottom, f32 top, f32 near, f32 far)
{
	// Matrix4 m;
	// m.col0.x = 2 / (right - left);
	// m.col1.y = 2 / (top - bottom);
	// m.col2.z = -2 / (far - near);
	// m.col3 = Vector4(-(right + left) / (right - left), -(top + bottom) /
	// (top-bottom), -(far + near) / (far - near), 1);
	// return m;

	Matrix4 result;

	result[0][0] = 2.0f / (right - left);
	result[1][1] = 2.0f / (top - bottom);
	result[2][2] = -2.0f / (far - near);
	result[3][0] = -(right + left) / (right - left);
	result[3][1] = -(top + bottom) / (top - bottom);
	result[3][2] = -(far + near) / (far - near);

	return result;
}


} // namespace Teaser