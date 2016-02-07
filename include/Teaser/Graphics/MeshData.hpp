//------------------------------------------------------------
// <copyright file="MeshData.hpp" autor="Markus Perz">
//     Copyright (c) Markus Perz. All rights reserved.
// </copyright>
//------------------------------------------------------------

#ifndef TEASER_MESHDATA_MESH_HPP
#define TEASER_MESHDATA_MESH_HPP

#include <Teaser/Common.hpp>
#include <Teaser/Math.hpp>
#include <Teaser/Graphics/Vertex.hpp>

#include <vector>

namespace Teaser
{
using Indicie = unsigned int;

enum class DrawMode : GLenum
{
	TRIANGLES = GL_TRIANGLES,
	LINES = GL_LINES,
	POINTS = GL_POINTS, 
};

class MeshData
{

public:
	MeshData();
	~MeshData();

	void addFace(const Vertex& a, const Vertex& b, const Vertex& c, bool computeNormals = true);
	void addLine(const Vertex& a, const Vertex& b);

	void setDrawMode(DrawMode drawType);
	DrawMode getDrawMode() const;

	const Vertex* getVertexData() const;
	unsigned int getVertexCount() const;
	const Indicie* getIndiciesData() const;
	unsigned int getIndiciesCount() const;

private:
	DrawMode m_drawMode;
	std::vector<Vertex> m_verts;
	std::vector<Indicie> m_inds;

};
} // namespace Teaser

#endif //TEASER_MESHDATA_MESH_HPP