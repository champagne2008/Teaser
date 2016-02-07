//------------------------------------------------------------
// <copyright file="LineRenderer.cpp" autor="Markus Perz">
//     Copyright (c) Markus Perz. All rights reserved.
// </copyright>
//------------------------------------------------------------

#include <Teaser/Graphics/LineRenderer.hpp>

namespace Teaser
{

LineRenderer::LineRenderer() :m_vbo(0)
{}

LineRenderer::~LineRenderer() 
{

}

void LineRenderer::init() 
{
	m_shader.create();
	m_shader.addShaderFromFile(ShaderType::VertexShader,"data/shaders/LineShader.vert");
	m_shader.addShaderFromFile(ShaderType::FragmentShader, "data/shaders/LineShader.frag");
	m_shader.link();

	glGenVertexArrays(1, &m_vbo);
	glBindBuffer(GL_VERTEX_ARRAY, m_vbo);
}

void LineRenderer::renderLine(const Vector3& start,
	const Vector3& end,
	const Vector4& color)
{

	

	//Vector3 data[] = {start, end};

	//glBindBuffer(GL_VERTEX_ARRAY, m_vbo);
	//glBufferSubData(GL_VERTEX_ARRAY,0, sizeof(data), data);
	//glBindBuffer(GL_VERTEX_ARRAY,0);
	//
	m_shader.use()
	    .setUniform("u_color", color)
	    .setUniform("u_proj", m_proj)
	    .setUniform("u_view", m_view);


	glBegin(GL_LINES);
	glVertex3f(start.x, start.y, start.z);
	glVertex3f(end.x, end.y, end.z);
	glEnd();
	/*
	glBindBuffer(GL_VERTEX_ARRAY, m_vbo);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0,
		3,
		GL_FLOAT,
		GL_FALSE,
		sizeof(Vector3),
		0);

	glDrawArrays(GL_LINES, 0, 2);
	glBindBuffer(GL_VERTEX_ARRAY,0);*/
}

void LineRenderer::renderLine(const Vector3& start,
	const Vector3& direction,
	float length,
	const Vector4& color)
{
	Vector3 end = start + normalize(direction)*length;
	renderLine(start, end, color);
}

void LineRenderer::setViewMatrix(const Matrix4& view)
{
	m_view = view;
}

void LineRenderer::setProjectionMatrix(const Matrix4& proj) 
{
	m_proj = proj;
}

} // namespace Teaser