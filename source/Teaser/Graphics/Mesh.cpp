//------------------------------------------------------------
// <copyright file="Mesh.cpp" autor="Markus Perz">
//     Copyright (c) Markus Perz. All rights reserved.
// </copyright>
//------------------------------------------------------------

#include <Teaser/Graphics/Mesh.hpp>

namespace Teaser
{
Mesh::Mesh()
: m_vao(0)
, m_vertexCount(0)
, m_drawMode(DrawMode::TRIANGLES)
{
}

Mesh::Mesh(const MeshData& data)
: Mesh()
{
	create(data);
}

Mesh::~Mesh() { destroy(); }

void Mesh::create(const MeshData& data) 
{
	u32 ibo;
	u32 vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)*data.getVertexCount(), data.getVertexData(), GL_STATIC_DRAW);

	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indicie)*data.getIndiciesCount(), data.getIndiciesData(), GL_STATIC_DRAW);

	glGenVertexArrays(1,&m_vao);
	glBindVertexArray(m_vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

	glEnableVertexAttribArray(VERTEX_POSITION);
	glEnableVertexAttribArray(COLOR_POSITION);
	glEnableVertexAttribArray(UV_POSITION);

	glVertexAttribPointer(VERTEX_POSITION,
		3,
		GL_FLOAT,
		GL_FALSE,
		Vertex::size(),
		(const void*)Vertex::offsetPosition());
	glVertexAttribPointer(COLOR_POSITION,
		3,
		GL_FLOAT,
		GL_FALSE,
		Vertex::size(),
		(const void*)Vertex::offsetColor());
	glVertexAttribPointer(UV_POSITION,
		2,
		GL_FLOAT,
		GL_FALSE,
		Vertex::size(),
		(const void*)Vertex::offsetUV());
	glBindVertexArray(0);

	m_vertexCount = data.getIndiciesCount();
	m_drawMode = data.getDrawMode();

}

void Mesh::destroy() 
{
	glDeleteVertexArrays(1,&m_vao);
	m_vertexCount = 0;
}

} // namespace Teaser