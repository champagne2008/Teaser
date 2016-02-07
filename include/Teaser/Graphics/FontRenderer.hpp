#ifndef TEASER_FONTRENDERER_HPP
#define TEASER_FONTRENDERER_HPP

#include <Teaser/Common.hpp>
#include <Teaser/Math.hpp>
#include <Teaser/Global.hpp>
#include <Teaser/Window.hpp>

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

	void init();
	void renderText(std::string text, float x, float y, float scale, const Vector4& color);
	void renderText(std::string text,
	                const Vector2& pos,
	                float scale,
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
	Global<Window> window;
};

} // namespace Teaser

#endif // TEASER_FONTRENDERER_HPP
