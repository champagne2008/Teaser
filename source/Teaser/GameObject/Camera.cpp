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
		gameObject->transform.setPosition(0, 0, 30);
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
		gameObject->transform.setPosition(Vector3(pos.x, pos.y, pos.z));

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
		if(lookAtCam)
		{
			Vec3 t;
			if (target)
				t = target->transform.getPosition();

			view = lookAt(gameObject->transform.getPosition(), t, gameObject->transform.getUp());
		}
		else
			view = lookAt(gameObject->transform.getPosition(), gameObject->transform.getPosition() + gameObject->transform.getForward(), gameObject->transform.getUp());
	}
	void Camera::calculateProj()
	{
		proj = perspective(fovy, aspect, nearPlane, farPlane);
	}



} // namespace Teaser