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

	Vector3 position;
	Vector3 color;
	Vector2 uv;
	Vector3 normal;

	static constexpr size_t offsetPosition() { return offsetof(Vertex, position); }
	static constexpr size_t offsetColor() { return offsetof(Vertex, color); }
	static constexpr size_t offsetUV() { return offsetof(Vertex, uv); }
	static constexpr size_t offsetNormal() { return offsetof(Vertex, normal); }
	static constexpr f32 size() { return sizeof(Vertex); }

	bool operator < (const Vertex& other) const;
	bool operator == (const Vertex& other) const;
};

} // namespace Teaser

#endif // TEASER_VERTEX_HPP