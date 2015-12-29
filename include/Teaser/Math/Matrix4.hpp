//------------------------------------------------------------
// <copyright file="Matrix.hpp" autor="Markus Perz">
//     Copyright (c) Markus Perz. All rights reserved.
// </copyright>
//------------------------------------------------------------

#ifndef TEASER_MATH_MATRIX_HPP
#define TEASER_MATH_MATRIX_HPP

#include <Teaser/Common.hpp>
#include <Teaser/Math/Vector4.hpp>

#include <iomanip>

namespace Teaser
{
class Matrix4
{
public:
	//Creates identity matrix
	Matrix4()
	: col0(1, 0, 0, 0)
	, col1(0, 1, 0, 0)
	, col2(0, 0, 1, 0)
	, col3(0, 0, 0, 1)
	{
	}

	Matrix4(f32 t)
		: col0(t, 0, 0, 0)
		, col1(0, t, 0, 0)
		, col2(0, 0, t, 0)
		, col3(0, 0, 0, t)
	{
	}

	Matrix4(const Matrix4& other) :
		col0(other.col0)
		, col1(other.col1)
		, col2(other.col2)
		, col3(other.col3)
	{
	
	}

	Matrix4(Vector4 c0, Vector4 c1, Vector4 c2, Vector4 c3 )
		: col0(c0)
		, col1(c1)
		, col2(c2)
		, col3(c3)
	{
	}

	~Matrix4() {}

	union {
		Vector4 data[4];

		struct
		{
			f32 m00;
			f32 m01;
			f32 m02;
			f32 m03;

			f32 m10;
			f32 m11;
			f32 m12;
			f32 m13;

			f32 m20;
			f32 m21;
			f32 m22;
			f32 m23;

			f32 m30;
			f32 m31;
			f32 m32;
			f32 m33;
		};

		struct
		{
			Vector4 col0;
			Vector4 col1;
			Vector4 col2;
			Vector4 col3;
		};
	};

	Vector4 operator [](int index) const { return data[index]; }
	Vector4& operator [](int index) { return data[index]; }
};

std::ostream & operator << (std::ostream & stream, const Matrix4& other) 
{
	stream  << "Matrix4( "
		<< std::setw(6) << other.m00
		<< std::setw(6) << other.m10
		<< std::setw(6) << other.m20
		<< std::setw(6) << other.m30 << std::endl
		
		<< std::setw(15) << other.m01
		<< std::setw(6)  << other.m11
		<< std::setw(6)  << other.m21
		<< std::setw(6)  << other.m31 << std::endl
		
		<< std::setw(15) << other.m02
		<< std::setw(6)  << other.m12
		<< std::setw(6)  << other.m22
		<< std::setw(6)  << other.m32 << std::endl
		
		<< std::setw(15) << other.m03
		<< std::setw(6)  << other.m13
		<< std::setw(6)  << other.m23
		<< std::setw(6)  << other.m33 << ")"<< std::endl;

	return stream;
}


} // namespace Teaser

#endif // TEASER_MATH_MATRIX_HPP