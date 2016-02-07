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

Mesh::~Mesh() { }

void Mesh::create(const MeshData& data) 
{
	unsigned int ibo;
	unsigned int vbo;
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

void drawMesh(ShaderProgram& shader, const Matrix4& model, const Matrix4& camera, const Matrix4& projection, Mesh& mesh) 
{
	//shader.use().setUniform("u_view", camera).setUniform("u_model", model).setUniform("u_proj", projection).setUniform("tex", 0);

	Matrix4 mvp = projection * camera  * model;
	shader.use().setUniform("u_mvp", mvp).setUniform("tex", 0);
	mesh.bind();
	glDrawElements(mesh.getDrawMode(), mesh.getCount(), GL_UNSIGNED_INT,0);
	mesh.unbind();
	shader.unUse();
}


MeshData generateCubeData(float size)
{

	float cshalf = size / 2.0f;

	MeshData md;

	Vertex pos[4] = {
		{ Vector3(-cshalf, -cshalf,  cshalf), Vector3(1.0, 1.0, 1.0), Vector2(0.0 , 1.0) },
		{ Vector3(cshalf, -cshalf,  cshalf), Vector3(1.0, 1.0, 1.0), Vector2(1.0 , 1.0) },
		{ Vector3(cshalf,  cshalf,  cshalf), Vector3(1.0, 1.0, 1.0), Vector2(1.0 , 0.0) },
		{ Vector3(-cshalf,  cshalf,  cshalf), Vector3(1.0, 1.0, 1.0), Vector2(0.0 , 0.0) }
	};

	Matrix4 rotateY = rotate(Degree(90), { 0,1,0 });
	for (unsigned int i = 0; i < 4; i++)
	{
		md.addFace(pos[0], pos[1], pos[2]);
		md.addFace(pos[2], pos[3], pos[0]);

		for (unsigned int k = 0; k < 4; k++)
		{
			Vector4 tmp(pos[k].position.x, pos[k].position.y, pos[k].position.z, 1);
			tmp = rotateY * tmp;
			pos[k].position = Vector3(tmp.x, tmp.y, tmp.z);
		}
	}

	//Generating Top and Bot Face
	for (unsigned int i = 1; i < 3; i++)
	{
		for (unsigned int k = 0; k < 4; k++)
		{
			Vector4 tmp(pos[k].position.x, pos[k].position.y, pos[k].position.z, 1);
			tmp = rotate(Degree(90 * i), { 1,0 ,0 }) * tmp;
			pos[k].position = Vector3(tmp.x, tmp.y, tmp.z);
		}

		md.addFace(pos[0], pos[1], pos[2]);
		md.addFace(pos[2], pos[3], pos[0]);
	}

	return md;
}

MeshData generateGridData(unsigned int tilesX, unsigned int tilesY,float gridSize, Vec3 color)
{

	MeshData md;

	float xOffset = gridSize*tilesX / 2;
	float yOffset = gridSize*tilesY / 2;

	for (unsigned int x = 0; x < tilesX + 1; x++)
	{
		float offsetedX = x*gridSize - xOffset;
		float offsetedY = tilesY*gridSize - yOffset;

		md.addLine({ Vector3(offsetedX,0,-yOffset),color,Vector2(0,0) }, { Vector3(offsetedX,0,offsetedY),color,Vector2(0,0) });
	}

	for (unsigned int y = 0; y < tilesY + 1; y++)
	{
		float offsetedY = y*gridSize - yOffset;
		float offsetedX = tilesX*gridSize - xOffset;
		md.addLine({ Vector3(-xOffset,0,offsetedY),color,Vector2(0,0) }, { Vector3(offsetedX,0,offsetedY),color,Vector2(0,0) });
	}

	md.setDrawMode(DrawMode::LINES);
	return md;
}

} // namespace Teaser