//------------------------------------------------------------
// <copyright file="Mesh.hpp" autor="Markus Perz">
//     Copyright (c) Markus Perz. All rights reserved.
// </copyright>
//------------------------------------------------------------

#ifndef TEASER_MESH_HPP
#define TEASER_MESH_HPP

#include <Teaser/Common.hpp>
#include <Teaser/Graphics/MeshData.hpp>
#include <Teaser/Graphics/ShaderProgram.hpp>
#include <Teaser/Math.hpp>
#include <Teaser/GameObjects.hpp>

namespace Teaser
{

class Mesh:public Component
{

	enum : unsigned int
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
	inline unsigned int getCount();
	inline GLenum getDrawMode();

private:
	GLuint m_vao;
	unsigned int m_vertexCount;
	DrawMode m_drawMode;
};

inline void Mesh::bind() { glBindVertexArray(m_vao); }

inline void Mesh::unbind() { glBindVertexArray(0); }

inline unsigned int Mesh::getCount() { return m_vertexCount; }

inline GLenum Mesh::getDrawMode() { return (GLenum)m_drawMode; }

void drawMesh(ShaderProgram& shader, const Matrix4& model, const Matrix4& camera, const Matrix4& projection, Mesh& mesh);

MeshData generateCubeData(float size);
MeshData generateGridData(unsigned int tilesX, unsigned int tilesY, float gridSize, Vec3 color = Vec3(1));

} // namespace Teaser

#endif // TEASER_MESH_HPP