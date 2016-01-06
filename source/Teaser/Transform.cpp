//------------------------------------------------------------
// <copyright file="Transform.cpp" autor="Markus Perz">
//     Copyright (c) Markus Perz. All rights reserved.
// </copyright>
//------------------------------------------------------------

#include <Teaser/Transform.hpp>

namespace Teaser
{
Transform::Transform()
: m_position(0, 0, 0)
, m_rotation()
, m_scale(1, 1, 1)
, m_matrix()
, m_dirty(true)
{
}

Transform::~Transform() {}

Matrix4 Transform::getMatrix() const
{

	if (m_dirty)
	{
		// update Matrix
		m_matrix = Teaser::translate(m_position) *
		           m_rotation.getRotationMatrix() * Teaser::scale(m_scale);

		m_dirty = false;
	}
	return m_matrix;
}

Matrix4 Transform::getInverse() const { return inverse(getMatrix()); }

Quaternion Transform::getRotation() const { return m_rotation; }
Vector3 Transform::getEulerAngles() const
{
	// TODO: Implement this
	// return m_rotation.getEulerAxis();
	tassert(false, "Not yet implemented");
	return Vector3();
}

Vector3 Transform::getPosition() const { return m_position; }
Vector3 Transform::getScale() const { return m_scale; }

void Transform::setRotation(const Quaternion& rotation)
{
	if (rotation != m_rotation)
	{
		m_rotation = rotation;
		m_dirty    = true;
	}
}

void Transform::setRotation(const Vector3& eulerAngles)
{
	tassert(false, "Not yet implemented");
	// setRotation(Quaternion::fromEulerAngle(eulerAngles));
}

void Transform::setRotation(f32 yaw, f32 pitch, f32 roll)
{
	tassert(false, "Not yet implemented");
	// setRotation(Quaternion::fromEulerAngle(yaw,pitch,roll));
}

void Transform::setRotation(const Angle& angle, const Vector3& axis)
{
	setRotation(Quaternion::fromAxisAngle(angle, axis));
}

void Transform::rotate(const Quaternion& rotation)
{
	if (rotation != Quaternion::Identity)
	{
		m_rotation = rotation * m_rotation;
		m_dirty    = true;
	}
}
void Transform::rotate(const Vector3& eulerAngles)
{
	tassert(false, "Not yet implemented");
	// rotate(Quaternion::fromEulerAngle(eulerAngles));
}

void Transform::rotate(f32 yaw, f32 pitch, f32 roll)
{
	tassert(false, "Not yet implemented");
	// rotate(Quaternion::fromEulerAngle(yaw,pitch,roll));
}

void Transform::rotate(const Angle& angle, const Vector3& axis)
{
	rotate(Quaternion::fromAxisAngle(angle, axis));
}

void Transform::setPosition(const Vector3& position)
{
	if (m_position != position)
	{
		m_position = position;
		m_dirty    = true;
	}
}

void Transform::setPosition(f32 x, f32 y, f32 z) 
{
	setPosition(Vector3(x,y,z));
}

void Transform::translate(const Vector3& translation) 
{
	if (translation != Vector3::Zero) 
	{
		m_position += translation;
		m_dirty = true;
	}
}

void Transform::translate(f32 x, f32 y, f32 z) 
{
	translate(Vector3(x, y, z));
}

void Transform::setScale(const Vector3& scale) 
{
	if (m_scale != scale)
	{
		m_scale = scale;
		m_dirty = true;
	}
}
void Transform::setScale(f32 sx, f32 sy, f32 sz) 
{
	setScale(Vector3(sx, sy, sz));
}
void Transform::setScale(f32 sxyz) 
{
	setScale(Vector3(sxyz)); //creates Vector with x=y=z=sxyz;
}

void Transform::scale(const Vector3& scale) 
{
	if (scale != Vector3(1,1,1)) 
	{
		m_scale = m_scale * scale;
		m_dirty = true;
	}
}
void Transform::scale(f32 sx, f32 sy, f32 sz)
{
	scale(Vector3(sx, sy, sz));
}
void Transform::scale(f32 sxyz)
{
	scale(Vector3(sxyz));
}

Vector3 Transform::getRight() const 
{
	return Vector3(1, 0, 0)*m_rotation;
}
Vector3 Transform::getLeft() const
{
	return Vector3(-1, 0, 0)*m_rotation;
}
Vector3 Transform::getUp() const
{
	return Vector3(0, 1, 0)*m_rotation;
}
Vector3 Transform::getDown() const
{
	return Vector3(0, -1, 0)*m_rotation;
}
Vector3 Transform::getForward() const
{
	return Vector3(0, 0, 1)*m_rotation;
}
Vector3 Transform::getBackward() const
{
	return Vector3(0, 0, -1)*m_rotation;
}

} // namespace Teaser