//------------------------------------------------------------
// <copyright file="Angle.hpp" autor="Markus Perz">
//     Copyright (c) Markus Perz. All rights reserved.
// </copyright>
//------------------------------------------------------------

#ifndef TEASER_MATH_ANGLE_HPP
#define TEASER_MATH_ANGLE_HPP

#include <Teaser/Common.hpp>

namespace Teaser
{

	class Angle
	{
	public:

		enum Type { Radians, Degrees };
		Angle():m_radians(0) {};

		Angle(float angle) :m_radians(angle) {};

		Angle(float angle, Type type) 
		{
			switch (type)
			{
			default:
			case Radians: {
				m_radians = angle;
				break; }
			case Degrees:{
				m_radians = angle * toRad;
				break;
			}
			}
		};

		~Angle() {};

		inline float radians() const { return m_radians; }
		inline float degrees() const { return m_radians * toDeg; }

	private:

		const double toDeg = 180.0f / PI;
		const double toRad = PI / 180.0f;

		float m_radians;
	};

} // namespace Teaser

#endif //TEASER_MATH_ANGLE_HPP