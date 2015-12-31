//------------------------------------------------------------
// <copyright file="SpriteRenderer.cpp" autor="Markus Perz">
//     Copyright (c) Markus Perz. All rights reserved.
// </copyright>
//------------------------------------------------------------

#include <Teaser/SpriteRenderer.hpp>

namespace Teaser
{

	void SpriteRenderer::init(int width, int height) 
	{
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

		m_shader.create();
		m_shader.addShaderFromFile(ShaderType::VertexShader, "data/shaders/sprite-shader.vert");
		m_shader.addShaderFromFile(ShaderType::FragmentShader, "data/shaders/sprite-shader.frag");
		
		m_shader.link();


		glGenVertexArrays(1, &m_vao);

		glBindVertexArray(m_vao);

		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);

		glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,sizeof(f32)*4,0);
		glVertexAttribPointer(1,2, GL_FLOAT, GL_FALSE, sizeof(f32) * 4, (const void*)(sizeof(f32)*2));

		glBindVertexArray(0);


		m_ortho = ortho(0, width, 0, height, 0, 1000);
	}

	void SpriteRenderer::render(Texture& sprite, f32 x, f32 y, f32 w, f32 h, Angle rotZ) 
	{
		m_shader.use();
		sprite.bind();
		glActiveTexture(GL_TEXTURE0);
		m_shader.setUniform("u_sprite", 0);

		Matrix4 model = translate((w / 2)+x, (h / 2)+y, 0)*rotate(rotZ,Vector3(0,0,1))*translate(-w / 2, -h / 2, 0) *scale(w,h,2);

		m_shader.setUniform("u_model", model);
		m_shader.setUniform("u_proj", m_ortho);

		glBindVertexArray(m_vao);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);
		// glDrawArrays(GL_TRIANGLES, 0, 6);
		glBindVertexArray(0);

		m_shader.unUse();
	}



} // namespace Teaser