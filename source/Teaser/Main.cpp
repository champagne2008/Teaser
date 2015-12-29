//------------------------------------------------------------
// <copyright file="Main.cpp" autor="Markus Perz">
//     Copyright (c) Markus Perz. All rights reserved.
// </copyright>
//------------------------------------------------------------

#include <Teaser/Common.hpp>
#include <Teaser/Math.hpp>
#include <Teaser/ShaderProgram.hpp>

#include <iostream>

using namespace std;
using namespace Teaser;

const int WIDTH = 1260, HEIGHT = 870;

struct Vertex
{

	Vector3 vertPos;
	Vector3 vertColor;
};

void main()
{

	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Window* window = SDL_CreateWindow("First Window",
	                                      SDL_WINDOWPOS_CENTERED,
	                                      SDL_WINDOWPOS_CENTERED,
	                                      WIDTH,
	                                      HEIGHT,
	                                      SDL_WINDOW_OPENGL);

	bool running = true;

	SDL_GLContext glContext = SDL_GL_CreateContext(window);

	// TODO(Markus): Add better error-checking later
	if (glContext == nullptr)
	{
		cerr << "Failed to create OpenGL context" << endl;
		running = false;
	}

	glewExperimental = true;

	if (glewInit() != GLEW_OK)
	{
		cerr << "Failed to initialise GLEW" << endl;
		running = false;
	}

	glClearColor(0.3f, 0.4f, 0.8f, 1.0f);
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glViewport(0, 0, WIDTH, HEIGHT);

	Vertex verts[] = {
	    //    	x	  y	   z	  r		g	  b
	    {Vector3(-0.5, -0.5, 0.0), Vector3(0.0f, 1.0f, 1.0f)},
	    {Vector3(0.5, -0.5, 0.0), Vector3(1.0f, 0.0f, 1.0f)},
	    {Vector3(0.5, 0.5, 0.0), Vector3(0.0f, 1.0f, 0.0f)},
	    {Vector3(-0.5, 0.5, 0.0), Vector3(1.0f, 0.0f, 0.0f)},
	};

	u16 inds[] = {0, 1, 2, 2, 3, 0};

	u32 ibo;
	u32 vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);

	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(inds), inds, GL_STATIC_DRAW);

	ShaderProgram shader;
	shader.create();
	bool status = true;
	if (!shader.addShaderFromFile(ShaderType::VertexShader,
	                              "data/shaders/default.vert") ||
	    !shader.addShaderFromFile(ShaderType::FragmentShader,
	                              "data/shaders/default.frag"))
	{
		cerr << shader.getError() << endl;
		running = false;
	}

	if (!shader.link())
	{
		cerr << shader.getError() << endl;
	}

	shader.use();

	SDL_Event evt;

	// shader.setUniform("u_translation",(const
	// GLfloat*)Math::rotateZ(Angle(90,Angle::Degrees)).data);

	while (running)
	{
		SDL_PollEvent(&evt);

		switch (evt.type)
		{
		case SDL_QUIT:
			running = false;
			break;
		}
		glClear(GL_COLOR_BUFFER_BIT);

		shader.setUniform(
		    "u_translation",
		    Math::rotateZ(Angle(SDL_GetTicks() / 20.0f, Angle::Degrees)));

		{
			glBindBuffer(GL_ARRAY_BUFFER, vbo);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

			glEnableVertexAttribArray(0);
			glEnableVertexAttribArray(1);

			glVertexAttribPointer(
			    0, 3, GL_FLOAT, GL_FALSE, (sizeof(f32) * 6), 0);
			glVertexAttribPointer(1,
			                      3,
			                      GL_FLOAT,
			                      GL_FALSE,
			                      (sizeof(f32) * 6),
			                      (const void*)(sizeof(f32) * 3));

			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);
			// glDrawArrays(GL_TRIANGLES, 0, 6);

			glDisableVertexAttribArray(1);
			glDisableVertexAttribArray(0);
		}

		SDL_GL_SwapWindow(window);
	}

	SDL_DestroyWindow(window);
	SDL_Quit();
}
