//------------------------------------------------------------
// <copyright file="SpriteRenderer.hpp" autor="Markus Perz">
//     Copyright (c) Markus Perz. All rights reserved.
// </copyright>
//------------------------------------------------------------

#ifndef TEASER_SPRITERENDERER_HPP
#define TEASER_SPRITERENDERER_HPP

#include <Teaser/Common.hpp>
#include <Teaser/Math.hpp>
#include <Teaser/Texture.hpp>
#include <Teaser/ShaderProgram.hpp>

namespace Teaser
{

class SpriteRenderer
{
public:
	SpriteRenderer() {};
	~SpriteRenderer() {};

	void init(int width, int height);
	void render(Texture& sprite, f32 x, f32 y, f32 w, f32 h, Angle rotZ);

private:

	u32 m_vao;
	Matrix4 m_ortho;
	ShaderProgram m_shader;
};

} // namespace Teaser

#endif // TEASER_SPRITERENDERER_HPP