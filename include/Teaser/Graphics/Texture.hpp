//------------------------------------------------------------
// <copyright file="Texture.hpp" autor="Markus Perz">
//     Copyright (c) Markus Perz. All rights reserved.
// </copyright>
//------------------------------------------------------------
#ifndef TEASER_TEXTURE_HPP
#define TEASER_TEXTURE_HPP

#include <Teaser/Common.hpp>
#include <SOIL/SOIL.h>

namespace Teaser
{

class Texture
{
public:
	enum Format : GLenum
	{
		RGB  = GL_RGB,
		RGBA = GL_RGBA
	};

	Texture()
	: m_width(0)
	, m_height(0)
	, m_handle(0)
	{
	}

	Texture(GLuint id,unsigned int width, unsigned int height)
		: m_width(width)
		, m_height(height)
		, m_handle(id)
	{
	}

	~Texture() { destroy(); };

	void create();
	void loadData(unsigned char* data, unsigned int width, unsigned int height, Format format);
	void destroy();

	inline void bind() { glBindTexture(GL_TEXTURE_2D, m_handle); }
	inline void unbind() { glBindTexture(GL_TEXTURE_2D, 0); };

	void setPixelsAt(int x, int y, unsigned char*);
	unsigned char* getPixelAt(int x, int y);

	inline unsigned int getId() { return m_handle; }
	inline unsigned int getWidth() { return m_width; }
	inline unsigned int getHeight() { return m_height; }

	static Texture* loadTextureFromFile(std::string path);

private:
	Format m_format;
	unsigned int m_width;
	unsigned int m_height;
	unsigned int m_handle;
};


} // namespace Teaser

#endif // TEASER_TEXTURE_HPP
