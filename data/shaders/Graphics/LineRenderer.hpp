//------------------------------------------------------------
// <copyright file="LineRenderer.hpp" autor="Markus Perz">
//     Copyright (c) Markus Perz. All rights reserved.
// </copyright>
//------------------------------------------------------------

#ifndef TEASER_LINERENDERER_HPP
#define TEASER_LINERENDERER_HPP

#include <Teaser/Common.hpp>
#include <Teaser/Math.hpp>
#include <Teaser/Graphics/ShaderProgram.hpp>

namespace Teaser
{

class LineRenderer
{
public:
	LineRenderer();
	~LineRenderer();

	void init();
	void renderLine(const Vector3& start, const Vector3& end, const Vector4& color = Vector4(1, 1, 1, 1)) ;
	void renderLine(const Vector3& start, const Vector3& direction, f32 length, const Vector4& color = Vector4(1, 1, 1, 1));

	void setProjectionMatrix(const Matrix4& proj);
	void setViewMatrix(const Matrix4& view);

private:
	Matrix4 m_proj;
	Matrix4 m_view;

	GLuint m_vbo;
	ShaderProgram m_shader;
};

} // namespace Teaser

#endif // TEASER_LINERENDERER_HPP