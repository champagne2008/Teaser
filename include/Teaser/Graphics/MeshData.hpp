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
using Indicie = u32;

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

	void setDrawMode(DrawMode drawType);
	DrawMode getDrawMode() const;

	const Vertex* getVertexData() const;
	u32 getVertexCount() const;
	const Indicie* getIndiciesData() const;
	u32 getIndiciesCount() const;

private:
	DrawMode m_drawMode;
	std::vector<Vertex> m_verts;
	std::vector<Indicie> m_inds;

};
} // namespace Teaser

#endif //TEASER_MESHDATA_MESH_HPP