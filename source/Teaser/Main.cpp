//------------------------------------------------------------
// <copyright file="Main.cpp" autor="Markus Perz">
//     Copyright (c) Markus Perz. All rights reserved.
// </copyright>
//------------------------------------------------------------

#include <Teaser/Common.hpp>
#include <Teaser/Math.hpp>
#include <Teaser/SpriteRenderer.hpp>
#include <Teaser/Resources.hpp>

#include <SOIL/SOIL.h>
#include <iostream>

using namespace std;
using namespace Teaser;

GLOBAL int g_width  = 1260;
GLOBAL int g_height = 870;

GLOBAL SpriteRenderer g_spriteRenderer;

struct Vertex
{

	Vector3 vertPos;
	Vector3 vertColor;
	Vector2 vertUVs;

	static size_t offsetPosition() { return offsetof(Vertex, vertPos); }
	static size_t offsetColor() { return offsetof(Vertex, vertColor); }
	static size_t offsetUV() { return offsetof(Vertex, vertUVs); }

	static f32 size() { return sizeof(Vertex); }
};

void main()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Window* window = SDL_CreateWindow("First Window",
	                                      SDL_WINDOWPOS_CENTERED,
	                                      SDL_WINDOWPOS_CENTERED,
	                                      g_width,
	                                      g_height,
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
	glViewport(0, 0, g_width, g_height);

	g_textures.insert(Texture::loadTextureFromFile("data/images/cat.png"),"Cat");
	g_shaders.insert(ShaderProgram::loadShaderFromFile("data/shaders/default.vert", "data/shaders/default.frag"), "Default");

	g_textures["Cat"].bind();
	g_shaders["Default"].use();

	glActiveTexture(GL_TEXTURE0);
	g_shaders["Default"].setUniform("tex", 0);

	g_spriteRenderer.init(g_width,g_height);

	Matrix4 a(2);
	Matrix4 b(5);

	a = Math::translate(2, 3, 1);
	b = Math::scale(2, 2, 1);

	std::cout << a*b << endl;

	SDL_Event evt;
	while (running)
	{
		SDL_PollEvent(&evt);

		switch (evt.type)
		{
		case SDL_QUIT:
			running = false;
			break;
		}

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		{
			g_spriteRenderer.render(
			    g_textures["Cat"], 0, 0, 500, 400, Angle(0));
		}

		SDL_GL_SwapWindow(window);
	}

	SDL_DestroyWindow(window);
	SDL_Quit();
}
