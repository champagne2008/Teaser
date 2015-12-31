/*
This class was copied from the great learnopengl.com tutorial series
for more information visit :
http://www.learnopengl.com/#!In-Practice/Text-Rendering
*/

#include <Teaser/FontRenderer.hpp>

namespace Teaser
{

FontRenderer::FontRenderer()
{
	m_vao = 0;
	m_vbo = 0;
}

FontRenderer::~FontRenderer() {}

void FontRenderer::init(u32 width, u32 height)
{
	FT_Library ft;

	if (FT_Init_FreeType(&ft))
		fatal("FREETYPE: Could not init FreeType Library");

	FT_Face face;
	if (FT_New_Face(ft, "data/fonts/arial.ttf", 0, &face))
		fatal("FREETYPE: Failed to load font");

	FT_Set_Pixel_Sizes(face, 0, 48);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // Disable byte-alignment restriction

	for (GLubyte c = 0; c < 128; c++)
	{
		// Load character glyph
		if (FT_Load_Char(face, c, FT_LOAD_RENDER))
		{
			fatal("FREETYTPE: Failed to load Glyph " + c + std::string(" (") +
			      std::to_string(c) + (")"));
			continue;
		}

		// Generate texture
		GLuint texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(GL_TEXTURE_2D,
		             0,
		             GL_RED,
		             face->glyph->bitmap.width,
		             face->glyph->bitmap.rows,
		             0,
		             GL_RED,
		             GL_UNSIGNED_BYTE,
		             face->glyph->bitmap.buffer);
		// Set texture options
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		// Now store character for later use
		Character character;
		character.TextureID = texture;
		character.Size =
		    Vector2(face->glyph->bitmap.width, face->glyph->bitmap.rows);
		character.Bearing =
		    Vector2(face->glyph->bitmap_left, face->glyph->bitmap_top);
		character.Advance = face->glyph->advance.x;
		m_characters.insert(std::pair<GLchar, Character>(c, character));
	}

	FT_Done_Face(face);
	FT_Done_FreeType(ft);

	glGenVertexArrays(1, &m_vao);
	glGenBuffers(1, &m_vbo);
	glBindVertexArray(m_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(
	    GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	g_shaders.insert(
	    ShaderProgram::loadShaderFromFile("data/shaders/font-shader.vert",
	                                      "data/shaders/font-shader.frag"),
	    "FontShader");

	m_height = height;
	m_width  = width;

	updateProjectionMatrix();
}

void FontRenderer::updateProjectionMatrix()
{
	m_projection = ortho(0.0f, m_width, 0.0f, m_height, 0.0, 1000);
}

void FontRenderer::renderText(
    std::string text, f32 x, f32 y, f32 scale, const Vector4& color)
{

	// Activate corresponding render state
	glActiveTexture(GL_TEXTURE0);

	g_shaders["FontShader"]
	    .setUniform("textColor", color)
	    .setUniform("projection", m_projection)
	    .setUniform("text", 0);

	g_shaders["FontShader"].use();

	glBindVertexArray(m_vao);

	// Iterate through all characters

	std::string::const_iterator c;
	for (c = text.begin(); c != text.end(); c++)
	{
		Character ch = m_characters[*c];

		GLfloat xpos = x + ch.Bearing.x * scale;
		GLfloat ypos = y - (ch.Size.y - ch.Bearing.y) * scale;

		GLfloat w = ch.Size.x * scale;
		GLfloat h = ch.Size.y * scale;
		// Update VBO for each character
		GLfloat vertices[6][4] = {{xpos, ypos + h, 0.0, 0.0},
		                          {xpos, ypos, 0.0, 1.0},
		                          {xpos + w, ypos, 1.0, 1.0},

		                          {xpos, ypos + h, 0.0, 0.0},
		                          {xpos + w, ypos, 1.0, 1.0},
		                          {xpos + w, ypos + h, 1.0, 0.0}};

		// Render glyph texture over quad
		glBindTexture(GL_TEXTURE_2D, ch.TextureID);
		// Update content of VBO memory
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		// Render quad
		glDrawArrays(GL_TRIANGLES, 0, 6);
		// Now advance cursors for next glyph (note that advance is number of
		// 1/64 pixels)
		x += (ch.Advance >> 6) *
		     scale; // Bitshift by 6 to get value in pixels (2^6 = 64)
	}

	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void FontRenderer::renderText(std::string text,
                              const Vector2& pos,
                              GLfloat scale,
                              const Vector4& color)
{
	renderText(text, pos.x, pos.y, scale, color);
}

} // namespace Teaser
