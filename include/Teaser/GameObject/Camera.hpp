//------------------------------------------------------------
// <copyright file="Camera.hpp" autor="Markus Perz">
//     Copyright (c) Markus Perz. All rights reserved.
// </copyright>
//------------------------------------------------------------

#ifndef TEASER_CAMERA_HPP
#define TEASER_CAMERA_HPP


#include <Teaser/Common.hpp>
#include <Teaser/GameObjects.hpp>
#include <Teaser/Math.hpp>
#include <Teaser/Global.hpp>
#include <Teaser/Input.hpp>
#include <Teaser/Transform.hpp>

namespace Teaser
{
	class Camera : public Component
	{
	public:
		Camera(float fovy, float aspect, float nearPlane, float farPlane)
			:fovy(fovy), aspect(aspect), nearPlane(nearPlane), farPlane(farPlane)
		{
		}

		void start();

		void update(float dt);

		void doLookAt();

		void activate();

		Matrix4 getView();

		Matrix4 getProj();

		static Camera& active() { return *activeCamera; }


		GameObject* target;

	private:
		
		Global<Input> input;

		float x = 0, y = 0;
		float z = 10;


		virtual void calculateView();

		void calculateProj();

		bool projDirty = true;

		static Camera* activeCamera;
		Mat4 view, proj;
		float fovy, aspect, nearPlane, farPlane;
		
		bool lookAtCam = true;
	};

} // namespace Teaser

#endif //TEASER_CAMERA_HPP