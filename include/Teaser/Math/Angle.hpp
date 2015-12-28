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
	namespace Math
	{
		const double PI = 3.1415926;
	} // namespace Math

	class Angle
	{
	public:

		enum Type { Radians, Degrees };
		Angle():m_radians(0) {};
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

		inline f32 radians() { return m_radians; }
		inline f32 degrees() { return m_radians * toDeg; }

	private:

		const f32 toDeg = 180.0 / Math::PI;
		const f32 toRad = Math::PI / 180.0;

		f32 m_radians;
	};

} // namespace Teaser

#endif //TEASER_MATH_ANGLE_HPP