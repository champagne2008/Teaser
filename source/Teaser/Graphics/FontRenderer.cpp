/*
This class was copied from the great learnopengl.com tutorial series
for more information visit :
http://www.learnopengl.com/#!In-Practice/Text-Rendering
*/

#include <Teaser/Graphics/FontRenderer.hpp>
#include <Teaser/Math.hpp>
#include <Teaser/Resources.hpp>

namespace Teaser
{

FontRenderer::FontRenderer()
{
	m_vao = 0;
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
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
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

	float verts[] = {

		//	x	    y	   u	v
		0.0,  0.0, 0.0 , 1.0,
		1.0,  0.0, 1.0 , 1.0,
		1.0,  1.0, 1.0 , 0.0,
		0.0,  1.0, 0.0 , 0.0,

	};

	u16 inds[] = { 0, 1, 2, 2, 3, 0 };

	u32 ibo;
	u32 vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);

	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(inds), inds, GL_STATIC_DRAW);

	g_shaders.insert(
		ShaderProgram::loadShaderFromFile("data/shaders/font-shader.vert",
			"data/shaders/font-shader.frag"),
		"FontShader");

	glGenVertexArrays(1, &m_vao);

	glBindVertexArray(m_vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(f32) * 4, 0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(f32) * 4, (const void*)(sizeof(f32) * 2));

	glBindVertexArray(0);



	m_height = height;
	m_width  = width;

	updateProjectionMatrix();
}

void FontRenderer::updateProjectionMatrix()
{
	m_projection = ortho(0.0f, m_width, 0.0f, m_height);
}

void FontRenderer::renderText(
    std::string text, f32 x, f32 y, f32 scale, const Vector4& color)
{

	// Activate corresponding render state

	glActiveTexture(GL_TEXTURE0);

	g_shaders["FontShader"].use().setUniform("u_proj", m_projection).setUniform("u_sprite", 0).setUniform("u_color",color);

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

		x += (ch.Advance >> 6) *
		     scale; // Bitshift by 6 to get value in pixels (2^6 = 64)

		glBindTexture(GL_TEXTURE_2D, ch.TextureID);

		Matrix4 model = translate(xpos,ypos,0)*Teaser::scale(w, h, 1);
		g_shaders["FontShader"].setUniform("u_model", model);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);
	}

	glBindVertexArray(0);
}

void FontRenderer::renderText(std::string text,
                              const Vector2& pos,
                              GLfloat scale,
                              const Vector4& color)
{
	renderText(text, pos.x, pos.y, scale, color);
}

} // namespace Teaser
