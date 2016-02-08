//------------------------------------------------------------
// <copyright file="Camera.hpp" autor="Markus Perz">
//     Copyright (c) Markus Perz. All rights reserved.
// </copyright>
//------------------------------------------------------------

#include <Teaser/GameObject/Camera.hpp>

namespace Teaser
{
	Camera* Camera::activeCamera = nullptr;


	void Camera::start() 
	{
		gameObject->transform.setPosition(0, 10, 0);
		gameObject->transform.rotate(Degree(180), Vec3(0, 1, 0));
	}

	void Camera::update(float dt)
	{
		calculateView();
			doLookAt();

	}

	void Camera::doLookAt()
	{
		Vector2 mouseDelta = {};

		if (input->getMouseButtonDown(MouseButton::Left))
		{
			mouseDelta = input->getDeltaMouse();
		}

		z -= input->getMouseWheel() / 3.0f;
		z = clamp(1.0f, 50.0f, z);


		x -= mouseDelta.x / 3.0f;
		y += mouseDelta.y / 3.0f;

		y = clamp(-89.9f, 89.9f, y);

		Quaternion rot = quatFromAxisAngle(Degree(x), { 0, 1, 0 }) *
			quatFromAxisAngle(Degree(y), { 0, 0, 1 });

		Vector4 pos = rot.getRotationMatrix() * Vector4(z, 0, 0, 1);

		Vec3 tar = (target != nullptr) ? target->transform.getPosition() : Vec3(0);
		gameObject->transform.setPosition(toVec3(pos)+ tar);

	}

	void Camera::activate()
	{
		activeCamera = this;
	}

	Matrix4 Camera::getView()
	{
		return view;
	}

	Matrix4 Camera::getProj()
	{
		if (projDirty) {
			calculateProj();
			projDirty = false;
		}
		return proj;
	}

	void Camera::calculateView()
	{
		Vec3 tar = (target != nullptr)? target->transform.getPosition() : Vec3(0);
		view = lookAt(gameObject->transform.getPosition(), tar, gameObject->transform.getUp());
	}
	void Camera::calculateProj()
	{
		proj = perspective(fovy, aspect, nearPlane, farPlane);
	}



} // namespace Teaser