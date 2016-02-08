//------------------------------------------------------------
// <copyright file="Math.cpp" autor="Markus Perz">
//     Copyright (c) Markus Perz. All rights reserved.
// </copyright>
//------------------------------------------------------------

#include <Teaser/Math.hpp>

namespace Teaser
{

Matrix4 translate(float x, float y, float z)
{
	Matrix4 m;
	m[3] = Vector4(x, y, z, 1);
	return m;
}

Matrix4 scale(float x) { return scale(x, x, x); }

Matrix4 scale(float x, float y, float z)
{
	Matrix4 m;
	m[0][0] = x;
	m[1][1] = y;
	m[2][2] = z;
	return m;
}

Matrix4 rotate(Angle angle, const Vector3& v)
{
	const float c = cos(angle.radians());
	const float s = sin(angle.radians());

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

Matrix4 perspective(
    float left, float right, float bottom, float top, float near, float far)
{
	Matrix4 m;
	m.col0.x = 2 * near / (right - left);
	m.col1.y = 2 * near / (top - bottom);
	m.col2   = Vector4(0, 0, (far + near) / (far - near), -1);
	m.col3   = Vector4(0, 0, -2 * far * near / (far - near), 0);
	return m;
}

Matrix4 perspective(float fovy, float aspect, float zNear, float zFar)
{

	const float tanHalfFovy = tan(0.5f * fovy);

	Matrix4 result = {};
	result[0][0]   = 1.0f / (aspect * tanHalfFovy);
	result[1][1]   = 1.0f / (tanHalfFovy);
	result[2][2]   = -(zFar + zNear) / (zFar - zNear);
	result[2][3]   = -1.0f;
	result[3][2]   = -2.0f * zFar * zNear / (zFar - zNear);

	return result;
}

Matrix4 ortho(float left, float right, float bottom, float top)
{
	Matrix4 result; // is identity
	result[0][0] = (2) / (right - left);
	result[1][1] = (2) / (top - bottom);
	result[2][2] = -1;
	result[3][0] = -(right + left) / (right - left);
	result[3][1] = -(top + bottom) / (top - bottom);
	return result;
}

Matrix4
ortho(float left, float right, float bottom, float top, float near, float far)
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

Matrix4 lookAt(const Vector3& eye, const Vector3& target, const Vector3& up)
{
	Vector3 f = normalize(eye - target);
	Vector3 r = normalize(cross(up, f));
	Vector3 u = (cross(f, r));

	// Matrix4 orientation(Vector4(r.x, r.y, r.z, 0),
	//               Vector4(u.x, u.y, u.z, 0),
	//               Vector4(f.x, f.y, f.z, 0),
	//               Vector4(0, 0, 0, 1));

	Matrix4 orientation(Vector4(r.x, u.x, f.x, 0),
	                    Vector4(r.y, u.y, f.y, 0),
	                    Vector4(r.z, u.z, f.z, 0),
	                    Vector4(0, 0, 0, 1));

	Matrix4 translation = translate(-eye);

	return orientation * translation;
}

Quaternion quatFromMatrix(const Matrix4& m)
{
	float fourWSquaredMinus1 = m.m00 + m.m11 + m.m22;
	float fourXSquaredMinus1 = m.m00 - m.m11 - m.m22;
	float fourYSquaredMinus1 = m.m11 - m.m00 - m.m22;
	float fourZSquaredMinus1 = m.m22 - m.m00 - m.m11;

	int biggestIndex               = 0;
	float fourBiggestSquaredMinus1 = fourWSquaredMinus1;

	if (fourXSquaredMinus1 > fourBiggestSquaredMinus1)
	{
		fourBiggestSquaredMinus1 = fourXSquaredMinus1;
	}
	if (fourYSquaredMinus1 > fourBiggestSquaredMinus1)
	{
		fourBiggestSquaredMinus1 = fourYSquaredMinus1;
	}
	if (fourZSquaredMinus1 > fourBiggestSquaredMinus1)
	{
		fourBiggestSquaredMinus1 = fourZSquaredMinus1;
	}

	Quaternion q;

	float biggestValue = sqrt(fourBiggestSquaredMinus1 + 1)*0.5f;
	float mult = 0.25f / biggestValue;

	switch (biggestIndex)
	{
	case 0:
	{
		q.w = biggestValue;
		q.x = (m.m21 - m.m12) * mult;
		q.y = (m.m02 - m.m20) * mult;
		q.z = (m.m10 - m.m01) * mult;
		break;
	}

	case 1:
	{
		q.x = biggestValue;
		q.w = (m.m21 - m.m12) * mult;
		q.y = (m.m10 + m.m01) * mult;
		q.z = (m.m02 + m.m20) * mult;
		break;
	}

	case 2:
	{
		q.y = biggestValue;
		q.w = (m.m02 - m.m20) * mult;
		q.x = (m.m10 + m.m01) * mult;
		q.z = (m.m21 + m.m12) * mult;
		break;
	}

	case 3:
	{
		q.z = biggestValue;
		q.w = (m.m10 - m.m01) * mult;
		q.x = (m.m01 + m.m20) * mult;
		q.y = (m.m21 + m.m12) * mult;
		break;
	}
	}

	return q;
}

Quaternion
quatLookAt(const Vector3& eye, const Vector3& target, const Vector3& up)
{
	tassert(target != eye,
	        "QuatLookAt() : eyeposition cannot be target position");

	// forward and size vectors of the coordinate frame 
	const Vec3 f = normalize(eye - target);
	const Vec3 side = normalize(cross(up, f));

	// cross product of bisection and [0, 0, -1] gives you the 
	// half-sine values required to orientate [0, 0, -1] to f
	// the dot product gives you half the cosine
	Vec3 b = normalize(f + Vec3(0, 0, -1));
	const Quaternion p = Quaternion(dot(b, f), cross(b, f));

	// now we need an additional rotation around the f vector
	// to orientate the side vector.
	Vec3 r = Vec3(p.w*p.w + p.x*p.x - p.y*p.y - p.z*p.z,
		(2 * p.x * p.y) - (2 * p.w * p.z),
		2 * p.x * p.z + 2 * p.w * p.y);

	b = normalize(side+r);
	Quaternion q = Quaternion(dot(b, side), cross(side, b));
	// now we can take the product of q and p

	return q*p;
}

} // namespace Teaser