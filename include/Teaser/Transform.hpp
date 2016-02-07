//------------------------------------------------------------
// <copyright file="Transform.hpp" autor="Markus Perz">
//     Copyright (c) Markus Perz. All rights reserved.
// </copyright>
//------------------------------------------------------------

#ifndef TEASER_TRANSFORM_HPP
#define TEASER_TRANSFORM_HPP

#include <Teaser/Common.hpp>
#include <Teaser/Math.hpp>
//#include <Teaser/GameObjects.hpp>

#include <Teaser/GameObject/Component.hpp>

namespace Teaser
{


class Transform : public Component
{
public:
	Transform();
	~Transform();

	Matrix4 getMatrix() const;
	Matrix4 getInverse() const;

	Quaternion getRotation() const ;
	Vector3 getEulerAngles() const ;
	Vector3 getPosition() const ;
	Vector3 getScale() const ;

	void setRotation(const Quaternion& rotation);
	void setRotation(const Vector3& eulerAngles);
	void setRotation(float yaw, float pitch, float roll);
	void setRotation(const Angle& angle, const Vector3& axis);

	void rotate(const Quaternion& rotation);
	void rotate(const Vector3& eulerAngles);
	void rotate(float yaw, float pitch, float roll);
	void rotate(const Angle& angle, const Vector3& axis);

	void setPosition(const Vector3& position);
	void setPosition(float x, float y, float z);

	void translate(const Vector3& translation);
	void translate(float x, float y, float z);

	void setScale(const Vector3& scale);
	void setScale(float sx, float sy, float sz);
	void setScale(float sxyz);

	void scale(const Vector3& scale);
	void scale(float sx, float sy, float sz);
	void scale(float sxyz);

	Vector3 getRight() const;
	Vector3 getLeft() const;
	Vector3 getUp() const;
	Vector3 getDown() const;
	Vector3 getForward() const;
	Vector3 getBackward() const;

private:

	mutable bool m_dirty;

	mutable Matrix4 m_matrix;

	Vector3 m_scale;
	Vector3 m_position;
	Quaternion m_rotation;

};

} // namespace Teaser

#endif // TEASER_TRANSFORM_HPP