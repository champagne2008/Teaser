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
	~Texture(){};

	void create();
	void loadData(byte* data, u32 width, u32 height, Format format);
	void destroy();

	inline void bind() { glBindTexture(GL_TEXTURE_2D, m_handle); }
	inline void unbind() { glBindTexture(GL_TEXTURE_2D, 0); };

	void setPixelsAt(int x, int y, byte*);
	byte* getPixelAt(int x, int y);

	inline u32 getId() { return m_handle; }
	inline u32 getWidth() { return m_width; }
	inline u32 getHeight() { return m_height; }

	GLOBAL Texture* loadTextureFromFile(std::string path);

private:
	Format m_format;
	u32 m_width;
	u32 m_height;
	u32 m_handle;
};
} // namespace Teaser

#endif // TEASER_TEXTURE_HPP
