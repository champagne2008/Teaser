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

		Angle(f32 angle) :m_radians(angle) {};

		Angle(f32 angle, Type type) 
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

		inline f32 radians() const { return m_radians; }
		inline f32 degrees() const { return m_radians * toDeg; }

	private:

		const f64 toDeg = 180.0f / PI;
		const f64 toRad = PI / 180.0f;

		f32 m_radians;
	};

} // namespace Teaser

#endif //TEASER_MATH_ANGLE_HPP