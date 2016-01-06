//------------------------------------------------------------
// <copyright file="Quaternion.cpp" autor="Markus Perz">
//     Copyright (c) Markus Perz. All rights reserved.
// </copyright>
//------------------------------------------------------------

#include <Teaser/Math.hpp>
#include <Teaser/Math/Quaternion.hpp>

namespace Teaser
{
const Quaternion Quaternion::Identity =
    Quaternion(1, Vector3::Zero); // s = 1, v = ( 0, 0, 0);

Quaternion Quaternion::fromAxisAngle(const Angle& angle, const Vector3& axis)
{
	float a        = angle.radians();
	float half_sin = sin(0.5f * a);
	float half_cos = cos(0.5f * a);
	return Quaternion(half_cos, half_sin * axis.getNormalized());
}

Quaternion Quaternion::fromTwoVectors(const Vector3& u, const Vector3& v)
{
	float cos_theta = dot(Teaser::normalize(u), Teaser::normalize(v));
	float angle     = acos(cos_theta);
	Vector3 w       = Teaser::normalize(cross(u, v));
	return fromAxisAngle(angle, w);
}

Quaternion Quaternion::getConjugate() const
{
	Quaternion i(*this);

	i.v *= -1;

	return i;
}

Quaternion Quaternion::getInverse() const
{
	Quaternion q = getConjugate();
	return q / lengthSquared();
}

Quaternion& Quaternion::invert()
{
	Quaternion q = getInverse();
	for (u8 i = 0; i < 4; i++)
	{
		data[i] = q[i];
	}
	return *this;
}

AxisAngle Quaternion::getAxisAngle() const
{

	Quaternion q = getNormalized();
	f32 angle    = 2 * acos(q.w);
	f32 ax       = q.x / sqrt(1.0 - q.w * q.w);
	f32 ay       = q.y / sqrt(1.0 - q.w * q.w);
	f32 az       = q.z / sqrt(1.0 - q.w * q.w);

	return {Teaser::normalize({ax, ay, az}), angle};
}

Matrix4 Quaternion::getRotationMatrix() const
{
	Matrix4 mat;

	f32 xx = x * x;
	f32 xy = x * y;
	f32 xz = x * z;
	f32 xw = x * w;

	f32 yy = y * y;
	f32 yz = y * z;
	f32 yw = y * w;

	f32 zz = z * z;
	f32 zw = z * w;

	mat[0][0] = 1 - 2 * (yy + zz);
	mat[1][0] = 2 * (xy - zw);
	mat[2][0] = 2 * (xz + yw);

	mat[0][1] = 2 * (xy + zw);
	mat[1][1] = 1 - 2 * (xx + zz);
	mat[2][1] = 2 * (yz - xw);

	mat[0][2] = 2 * (xz - yw);
	mat[1][2] = 2 * (yz + xw);
	mat[2][2] = 1 - 2 * (xx + yy);

	return mat;
}

std::ostream& operator<<(std::ostream& stream, const Quaternion& q)
{

	stream << "Quaternion( s= " << q.s << ", v= " << q.v << ")";
	return stream;
}

Quaternion& Quaternion::operator+=(const Quaternion& other)
{
	s += other.s;
	v += other.v;
	return *this;
}

Quaternion& Quaternion::operator-=(const Quaternion& other)
{
	v -= other.v;
	s -= other.s;
	return *this;
}

Quaternion& Quaternion::operator*=(f32 scalar)
{
	s *= scalar;
	v *= scalar;
	return *this;
}

Quaternion& Quaternion::operator/=(f32 scalar)
{
	s /= scalar;
	v /= scalar;
	return *this;
}

Quaternion& Quaternion::operator*=(const Quaternion& other)
{
	Quaternion q = *this;
	*this        = q * other;
	return *this;
}

bool Quaternion::operator==(const Quaternion& other) const
{
	if (s != other.s || v != other.v)
		return false;

	return true;
}
bool Quaternion::operator!=(const Quaternion& other) const
{
	return !(*this == other);
}

Quaternion operator+(const Quaternion& lhs, const Quaternion& rhs)
{
	Quaternion q = lhs;
	q += rhs;
	return q;
}

Quaternion operator-(const Quaternion& lhs, const Quaternion& rhs)
{
	Quaternion q = lhs;
	q -= rhs;
	return q;
}

Quaternion operator*(const Quaternion& q, f32 scalar)
{
	Quaternion result = q;
	result *= scalar;
	return result;
}

Quaternion operator*(f32 scalar, const Quaternion& q)
{
	Quaternion result = q;
	result *= scalar;
	return result;
}

Quaternion operator/(const Quaternion& q, f32 scalar)
{
	Quaternion result = q;
	result /= scalar;
	return result;
}

Quaternion operator/(f32 scalar, const Quaternion& q)
{
	Quaternion result = q;
	result /= scalar;
	return result;
}

Quaternion operator*(const Quaternion& q1, const Quaternion& q2)
{
	f32 w = -q1.x * q2.x - q1.y * q2.y - q1.z * q2.z + q1.w * q2.w;
	f32 x = q1.x * q2.w + q1.y * q2.z - q1.z * q2.y + q1.w * q2.x;
	f32 y = -q1.x * q2.z + q1.y * q2.w + q1.z * q2.x + q1.w * q2.y;
	f32 z = q1.x * q2.y - q1.y * q2.x + q1.z * q2.w + q1.w * q2.z;

	return Quaternion(w, x, y, z);
}

Vector3 operator*(const Quaternion& q, const Vector3& vec)
{
	Vector3 vn(vec);
	vn.normalize();

	Quaternion vecQuat, resQuat;
	vecQuat.x = vn.x;
	vecQuat.y = vn.y;
	vecQuat.z = vn.z;
	vecQuat.w = 0.0f;

	resQuat = vecQuat * q.getConjugate();
	resQuat = q * resQuat;

	return (Vector3(resQuat.x, resQuat.y, resQuat.z));
}

Vector3 operator*(const Vector3& vec, const Quaternion& q) { return q * vec; }

} // namespace Teaser