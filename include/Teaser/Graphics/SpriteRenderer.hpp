//------------------------------------------------------------
// <copyright file="SpriteRenderer.hpp" autor="Markus Perz">
//     Copyright (c) Markus Perz. All rights reserved.
// </copyright>
//------------------------------------------------------------

#ifndef TEASER_SPRITERENDERER_HPP
#define TEASER_SPRITERENDERER_HPP

#include <Teaser/Common.hpp>
#include <Teaser/Math.hpp>
#include <Teaser/Graphics/Texture.hpp>
#include <Teaser/Graphics/ShaderProgram.hpp>
#include <Teaser/Global.hpp>
#include <Teaser/Window.hpp>

namespace Teaser
{

class SpriteRenderer
{
public:
	SpriteRenderer() {};
	~SpriteRenderer() {};

	void init();
	void render(Texture& sprite, float x, float y, float w, float h, Angle rotZ);

private:
	Global<Window> window;
	unsigned int m_vao;
	Matrix4 m_ortho;
	ShaderProgram m_shader;
};

} // namespace Teaser

#endif // TEASER_SPRITERENDERER_HPP