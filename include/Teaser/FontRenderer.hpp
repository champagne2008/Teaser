#ifndef TEASER_FONTRENDERER_HPP
#define TEASER_FONTRENDERER_HPP

#include <Teaser/Common.hpp>
#include <Teaser/Math.hpp>
#include <Teaser/Resources.hpp>

#include <map>

#include <ft2build.h>
#include FT_FREETYPE_H

namespace Teaser
{

class FontRenderer
{

public:
	enum Position
	{
		CENTERED
	};

	FontRenderer();
	virtual ~FontRenderer();

	void init(u32 width, u32 height);
	void
	renderText(std::string text, f32 x, f32 y, f32 scale, const Vector4& color);
	void renderText(std::string text,
	                const Vector2& pos,
	                f32 scale,
	                const Vector4& color);

protected:
	void updateProjectionMatrix();

	struct Character
	{
		GLuint TextureID; // ID handle of the glyph texture
		Vector2 Size;     // Size of glyph
		Vector2 Bearing;  // Offset from baseline to left/top of glyph
		GLuint Advance;   // Offset to advance to next glyph
	};

	Matrix4 m_projection;
	GLuint m_vao;
	std::map<GLchar, Character> m_characters;

	u32 m_width, m_height;
};

} // namespace Teaser

#endif // TEASER_FONTRENDERER_HPP
