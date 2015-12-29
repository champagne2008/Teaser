//------------------------------------------------------------
// <copyright file="Matrix4.cpp" autor="Markus Perz">
//     Copyright (c) Markus Perz. All rights reserved.
// </copyright>
//------------------------------------------------------------

#include <Teaser/Math/Matrix4.hpp>

namespace Teaser
{

std::ostream& operator<<(std::ostream& stream, const Matrix4& other)
{
	stream << "Matrix4( " << std::setw(6) << other.m00 << std::setw(6)
	       << other.m10 << std::setw(6) << other.m20 << std::setw(6)
	       << other.m30 << std::endl

	       << std::setw(15) << other.m01 << std::setw(6) << other.m11
	       << std::setw(6) << other.m21 << std::setw(6) << other.m31
	       << std::endl

	       << std::setw(15) << other.m02 << std::setw(6) << other.m12
	       << std::setw(6) << other.m22 << std::setw(6) << other.m32
	       << std::endl

	       << std::setw(15) << other.m03 << std::setw(6) << other.m13
	       << std::setw(6) << other.m23 << std::setw(6) << other.m33 << ")"
	       << std::endl;

	return stream;
}

} // namespace Teaser