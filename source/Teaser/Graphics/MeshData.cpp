//------------------------------------------------------------
// <copyright file="MeshData.cpp" autor="Markus Perz">
//     Copyright (c) Markus Perz. All rights reserved.
// </copyright>
//------------------------------------------------------------

#include <Teaser/Graphics/MeshData.hpp>

namespace Teaser
{

MeshData::MeshData(): m_drawMode(DrawMode::TRIANGLES) {}

MeshData::~MeshData() {}

void MeshData::addFace(const Vertex& a,
	const Vertex& b,
	const Vertex& c,
	bool computeNormals)
{
	Vector3 vec1 = b.position - a.position;
	Vector3 vec2 = c.position - a.position;
	Vector3 normal = normalize(cross(vec1, vec2));

	Vertex verts[3] = { a , b, c };

	for (unsigned int i = 0; i < 3; i++)
	{
		verts[i].normal = normal;
		bool found = false;
		for (unsigned int it = 0; it < m_verts.size(); it++)
		{
			if (m_verts[it] == verts[i])
			{
				m_inds.push_back(it);
				found = true;
				break;
			}
		}

		if (!found)
		{
			m_verts.push_back(verts[i]);
			m_inds.push_back(m_verts.size()-1);
		}
		//if m_verts contains verts[i] add ind ...
	}
}

void MeshData::addLine(const Vertex& a, const Vertex& b) 
{

	bool found = false;
	for (unsigned int it = 0; it < m_verts.size(); it++)
	{
		if (m_verts[it] == a)
		{
			m_inds.push_back(it);
			found = true;
			break;
		}
	}
	if (!found)
	{
		m_verts.push_back(a);
		m_inds.push_back(m_verts.size() - 1);
	}

    found = false;
	for (unsigned int it = 0; it < m_verts.size(); it++)
	{
		if (m_verts[it] == b)
		{
			m_inds.push_back(it);
			found = true;
			break;
		}
	}
	if (!found)
	{
		m_verts.push_back(b);
		m_inds.push_back(m_verts.size() - 1);
	}
}

void MeshData::setDrawMode(DrawMode drawType) 
{
	m_drawMode = drawType;
}
DrawMode MeshData::getDrawMode() const 
{
	return m_drawMode;
}
const Vertex* MeshData::getVertexData() const 
{
	return m_verts.data();
}
unsigned int MeshData::getVertexCount() const 
{
	return m_verts.size();
}
const Indicie* MeshData::getIndiciesData() const 
{
	return m_inds.data();
}
unsigned int MeshData::getIndiciesCount() const 
{
	return m_inds.size();
}

} // namespace Teaser
