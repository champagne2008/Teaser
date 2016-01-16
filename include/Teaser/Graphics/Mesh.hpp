//------------------------------------------------------------
// <copyright file="Mesh.hpp" autor="Markus Perz">
//     Copyright (c) Markus Perz. All rights reserved.
// </copyright>
//------------------------------------------------------------

#ifndef TEASER_MESH_HPP
#define TEASER_MESH_HPP

#include <Teaser/Common.hpp>
#include <Teaser/Graphics/MeshData.hpp>

namespace Teaser
{


class Mesh
{

	enum : u32
	{
		VERTEX_POSITION = 0,
		COLOR_POSITION  = 1,
		UV_POSITION     = 2,
		NORMAL_POSITION = 3
	};

public:
	Mesh();
	Mesh(const MeshData& data);
	~Mesh();

	void create(const MeshData& data);
	void destroy();
	inline void bind();
	inline void unbind();
	inline u32 getCount();
	inline DrawMode getDrawMode();

private:
	GLuint m_vao;
	u32 m_vertexCount;
	DrawMode m_drawMode;
};

inline void Mesh::bind() { glBindVertexArray(m_vao); }

inline void Mesh::unbind() { glBindVertexArray(0); }

inline u32 Mesh::getCount() { return m_vertexCount; }

} // namespace Teaser

#endif // TEASER_MESH_HPP