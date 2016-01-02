//------------------------------------------------------------
// <copyright file="Main.cpp" autor="Markus Perz">
//     Copyright (c) Markus Perz. All rights reserved.
// </copyright>
//------------------------------------------------------------

#include <Teaser/Common.hpp>
#include <Teaser/FontRenderer.hpp>
#include <Teaser/Math.hpp>
#include <Teaser/Resources.hpp>
#include <Teaser/SpriteRenderer.hpp>

#include <SOIL/SOIL.h>
#include <iostream>

using namespace std;
using namespace Teaser;

GLOBAL int g_width  = 1260;
GLOBAL int g_height = 870;

GLOBAL FontRenderer g_fontRenderer;
GLOBAL SpriteRenderer g_spriteRenderer;

GLOBAL Matrix4 g_camera;

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

struct Mesh
{
	u32 m_vao;
	u32 m_vertexCount;
};

GLOBAL Mesh g_cube;

u32 ibo;
u32 vbo;
void createCube()
{

	// clang-format off
	Vertex verts[] = {
	    {Vector3(-0.5, -0.5,  0.5), Vector3(1.0, 0.0, 0.0), Vector2(0.0 , 1.0)},
	    {Vector3( 0.5, -0.5,  0.5), Vector3(0.0, 0.0, 0.0), Vector2(1.0 , 1.0)},
	    {Vector3( 0.5,  0.5,  0.5), Vector3(0.0, 0.0, 1.0), Vector2(1.0 , 0.0)},
	    {Vector3(-0.5,  0.5,  0.5), Vector3(1.0, 1.0, 1.0), Vector2(0.0 , 0.0)},

		{ Vector3(-0.5, -0.5, -0.5), Vector3(1.0, 0.0, 0.0), Vector2(0.0 , 1.0) },
		{ Vector3( 0.5, -0.5, -0.5), Vector3(0.0, 0.1, 0.0), Vector2(1.0 , 1.0) },
		{ Vector3( 0.5,  0.5, -0.5), Vector3(0.0, 0.0, 1.0), Vector2(1.0 , 0.0) },
		{ Vector3(-0.5,  0.5, -0.5), Vector3(1.0, 1.0, 1.0), Vector2(0.0 , 0.0) },
	};

	u16 inds[] = { 
		0, 1, 2, 2, 3, 0,
		1, 5, 6, 6, 2, 1,
		5, 4, 7, 7, 6, 5,
		4, 0, 3, 3, 7, 4,
		3, 2, 6, 6, 7, 3,
		4, 5, 1, 1, 0, 4
	};

	// clang-format on

	u32 ibo;
	u32 vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);

	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(inds), inds, GL_STATIC_DRAW);

	glGenVertexArrays(1, &g_cube.m_vao);
	glBindVertexArray(g_cube.m_vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glVertexAttribPointer(0,
	                      3,
	                      GL_FLOAT,
	                      GL_FALSE,
	                      Vertex::size(),
	                      (const void*)Vertex::offsetPosition());
	glVertexAttribPointer(1,
	                      3,
	                      GL_FLOAT,
	                      GL_FALSE,
	                      Vertex::size(),
	                      (const void*)Vertex::offsetColor());
	glVertexAttribPointer(2,
	                      2,
	                      GL_FLOAT,
	                      GL_FALSE,
	                      Vertex::size(),
	                      (const void*)Vertex::offsetUV());
	glBindVertexArray(0);

	g_cube.m_vertexCount = sizeof(inds) / sizeof(u16);
}

void main()
{

	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Window* window = SDL_CreateWindow("Teaser",
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

	g_textures.insert(Texture::loadTextureFromFile("data/images/cat.png"),
	                  "Cat");
	g_textures.insert(Texture::loadTextureFromFile("data/images/box.png"),
	                  "Box");

	g_shaders.insert(
	    ShaderProgram::loadShaderFromFile("data/shaders/default.vert",
	                                      "data/shaders/default.frag"),
	    "default");

	g_spriteRenderer.init(g_width, g_height);
	g_fontRenderer.init(g_width, g_height);

	createCube();

	g_camera = lookAt(Vector3(5, 5, 5), Vector3(0, 0, 0), Vector3(0, 1, 0));

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
			g_spriteRenderer.render(g_textures["Cat"], 300, 200, 500, 400, 0);

			g_spriteRenderer.render(
			    g_textures["Cat"], 30, 20, 500, 400, Degree(30));

			g_spriteRenderer.render(
			    g_textures["Cat"], 600, 400, 500, 400, Degree(200));
		}

		g_shaders["default"].use();
		g_textures["Box"].bind();

		Matrix4 proj = perspective(70, g_width / (float)g_height, 0.01, 1000);
		Matrix4 model; // = translate(0, 0.0, sin(SDL_GetTicks() / 500.0) - 3);
		// *  rotate(Degree(SDL_GetTicks() / 20.0), Vector3(1, 1, 0));

		g_shaders["default"]
		    .setUniform("tex", 0)
		    .setUniform("u_model", model)
		    .setUniform("u_proj", proj)
		    .setUniform("u_view", g_camera);

		glBindVertexArray(g_cube.m_vao);

		glDrawElements(
		    GL_TRIANGLES, g_cube.m_vertexCount, GL_UNSIGNED_SHORT, 0);

		g_fontRenderer.renderText(
		    "Teaser Engine", {10, (float)(g_height - 60)}, 1, {1, 1, 1, 1});

		SDL_GL_SwapWindow(window);
	}

	SDL_DestroyWindow(window);
	SDL_Quit();
}
