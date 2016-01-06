//------------------------------------------------------------
// <copyright file="Vertex.hpp" autor="Markus Perz">
//     Copyright (c) Markus Perz. All rights reserved.
// </copyright>
//------------------------------------------------------------


#ifndef TEASER_VERTEX_HPP
#define TEASER_VERTEX_HPP

#include <Teaser/Common.hpp>
#include <Teaser/Math.hpp>

namespace Teaser
{
	struct Vertex
	{

		Vector3 vertPos;
		Vector3 vertColor;
		Vector2 vertUVs;

		static size_t offsetPosition() { return offsetof(Vertex, vertPos); }
		static size_t offsetColor() { return offsetof(Vertex, vertColor); }
		static size_t offsetUV() { return offsetof(Vertex, vertUVs); }

		static f32 size() { return sizeof(Vertex); }
	};

} // namespace Teaser

#endif //TEASER_VERTEX_HPP