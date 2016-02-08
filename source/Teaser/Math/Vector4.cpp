//------------------------------------------------------------
// <copyright file="Vector4.cpp" autor="Markus Perz">
//     Copyright (c) Markus Perz. All rights reserved.
// </copyright>
//------------------------------------------------------------

#include <Teaser/Math/Vector4.hpp>
namespace Teaser
{

	const Vector4 Vector4::Zero = Vector4(0, 0, 0, 0);

	std::string Vector4::toString() const
	{
		return std::string("Vector4( " + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + ", " + std::to_string(w) + ")");
	}

	Vector4& Vector4::operator*=(float f)
	{
		x *= f;
		y *= f;
		z *= f;
		w *= f;

		return *this;
	}

	Vector4& Vector4::operator/=(float f)
	{
		x /= f;
		y /= f;
		z /= f;
		w /= f;

		return *this;
	}

	Vector4& Vector4::operator+=(const Vector4& vec)
	{
		x += vec.x;
		y += vec.y;
		z += vec.z;
		w += vec.w;

		return *this;
	}

	Vector4& Vector4::operator-=(const Vector4& vec)
	{
		x -= vec.x;
		y -= vec.y;
		z -= vec.z;
		w -= vec.w;

		return *this;
	}

	bool Vector4::operator==(const Vector4& other) const
	{
		for (unsigned int i = 0; i < 4; i++)
		{
			if (data[i] != other[i])
				return false;
		}
		return true;
	}

	bool Vector4::operator !=(const Vector4& other) const
	{
		return !(*this == other);
	}

	std::ostream& operator<<(std::ostream& stream, const Vector4& vec)
	{
		stream << vec.toString();
		return stream;
	}

	Vector4 operator*(const Vector4& vec, float f)
	{
		return Vector4(vec.x * f, vec.y * f, vec.z * f, vec.w * f);
	}

	Vector4 operator*(float f, const Vector4& vec)
	{
		return Vector4(vec.x * f, vec.y * f, vec.z * f, vec.w * f);
	}

	Vector4 operator/(const Vector4& vec, float f)
	{
		return Vector4(vec.x / f, vec.y / f, vec.z / f, vec.w / f);
	}

	Vector4 operator/(float f, const Vector4& vec)
	{
		return Vector4(vec.x / f, vec.y / f, vec.z / f, vec.w / f);
	}

	Vector4 operator+(const Vector4& lhs, const Vector4& rhs)
	{
		return Vector4(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z, lhs.w + rhs.w);
	}

	Vector4 operator-(const Vector4& lhs, const Vector4& rhs)
	{
		return Vector4(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z, lhs.w - rhs.w);
	}

	// Hadamard Product
	Vector4 operator*(const Vector4& a, const Vector4& b)
	{
		Vector4 result;
		for (unsigned int i = 0; i < 4; i++)
			result[i] = a[i] * b[i];
		return result;
	}

	// Hadamard Product
	Vector4 operator/(const Vector4& a, const Vector4& b)
	{
		Vector4 result;
		for (unsigned int i = 0; i < 4; i++)
			result[i] = a[i] / b[i];
		return result;
	}

} // namespace Teaser