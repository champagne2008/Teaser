//------------------------------------------------------------
// <copyright file="Vertex.cpp" autor="Markus Perz">
//     Copyright (c) Markus Perz. All rights reserved.
// </copyright>
//------------------------------------------------------------

#include <Teaser/Graphics/Vertex.hpp>
#include <memory>
namespace Teaser
{
	bool Vertex::operator<(const Vertex& other)const 
	{
		return (memcmp(this, &other, sizeof(Vertex)) < 0)? true : false;
	}

	bool Vertex::operator == (const Vertex& other)const
	{
		return (position == other.position && color == other.color && uv == other.uv && normal == other.normal);
	}

} // namespace Teaser