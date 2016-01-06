//------------------------------------------------------------
// <copyright file="Main.cpp" autor="Markus Perz">
//     Copyright (c) Markus Perz. All rights reserved.
// </copyright>
//------------------------------------------------------------

#include <Teaser/Common.hpp>
#include <Teaser/Graphics.hpp>
#include <Teaser/Math.hpp>
#include <Teaser/Resources.hpp>
#include <Teaser/Transform.hpp>
#include <Teaser/Vertex.hpp>

#include <SOIL/SOIL.h>
#include <iostream>
#include <vector>

using namespace std;
using namespace Teaser;

GLOBAL int g_width  = 1260;
GLOBAL int g_height = 870;

GLOBAL FontRenderer g_fontRenderer;
GLOBAL SpriteRenderer g_spriteRenderer;
GLOBAL ParticleSystem g_particleSystem;

// GLOBAL Matrix4 g_camera;
GLOBAL Transform g_cubeTransform;

struct Mesh
{
	u32 vao;
	u32 vertexCount;
	GLenum drawMode;
};

GLOBAL Mesh g_cube;
GLOBAL Mesh g_grid;

struct Camera
{

	Transform transform;

} g_camera;

u32 ibo;
u32 vbo;
void createCube()
{

	// clang-format off
	Vertex verts[] = {
	    {Vector3(-0.5, -0.5,  0.5), Vector3(1.0, 0.0, 0.0), Vector2(0.0 , 1.0)},
	    {Vector3( 0.5, -0.5,  0.5), Vector3(0.0, 1.0, 0.0), Vector2(1.0 , 1.0)},
	    {Vector3( 0.5,  0.5,  0.5), Vector3(0.0, 0.0, 1.0), Vector2(1.0 , 0.0)},
	    {Vector3(-0.5,  0.5,  0.5), Vector3(1.0, 1.0, 1.0), Vector2(0.0 , 0.0)},

		{ Vector3(-0.5, -0.5, -0.5), Vector3(1.0, 0.0, 0.0), Vector2(0.0 , 1.0) },
		{ Vector3( 0.5, -0.5, -0.5), Vector3(0.0, 0.1, 0.0), Vector2(1.0 , 1.0) },
		{ Vector3( 0.5,  0.5, -0.5), Vector3(1.0, 0.0, 1.0), Vector2(1.0 , 0.0) },
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

	glGenVertexArrays(1, &g_cube.vao);
	glBindVertexArray(g_cube.vao);

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

	g_cube.vertexCount = sizeof(inds) / sizeof(u16);
	g_cube.drawMode    = GL_TRIANGLES;
}

void createGrid()
{

	LOCAL_PERSIST i8 tilesX = 30;
	LOCAL_PERSIST i8 tilesY = 30;

	LOCAL_PERSIST f32 gridSize = 0.5f;

	LOCAL_PERSIST Vector3 color = {0, 0, 0};

	std::vector<Vertex> verts;
	std::vector<u16> inds;
	// clang-format off

	f32 xOffset = gridSize*tilesX / 2;
	f32 yOffset = gridSize*tilesY / 2;

	int i = 0;
	for (u8 x = 0; x < tilesX+1; x++)
	{
		f32 offsetedX = x*gridSize - xOffset;
		f32 offsetedY = tilesY*gridSize - yOffset;

		verts.push_back({ Vector3(offsetedX,0,-yOffset),color,Vector2(0,0) });
		verts.push_back({ Vector3(offsetedX,0,offsetedY),color,Vector2(0,0) });

		inds.push_back(i++);
		inds.push_back(i++);
	}

	for (u8 y = 0; y < tilesY+1; y++)
	{
		f32 offsetedY = y*gridSize - yOffset;
		f32 offsetedX = tilesX*gridSize - xOffset;

		verts.push_back({ Vector3(-xOffset,0,offsetedY),color,Vector2(0,0) });
		verts.push_back({ Vector3(offsetedX,0,offsetedY),color,Vector2(0,0) });

		inds.push_back(i++);
		inds.push_back(i++);
	}

	// clang-format on

	u32 ibo;
	u32 vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER,
	             verts.size() * sizeof(Vertex),
	             verts.data(),
	             GL_STATIC_DRAW);

	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,
	             inds.size() * sizeof(u16),
	             inds.data(),
	             GL_STATIC_DRAW);

	glGenVertexArrays(1, &g_grid.vao);
	glBindVertexArray(g_grid.vao);

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

	g_grid.vertexCount = inds.size();
	g_grid.drawMode    = GL_LINES;
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
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LINE_SMOOTH);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glLineWidth(2);

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
	g_particleSystem.init();

	createCube();
	createGrid();

	Vector3 camPos = Vector3(3, 10, 5);

	bool dragging   = false;
	Vector2 lastPos = {};

	f32 x = 0, y = 0;
	f32 z = 10;
	while (running)
	{
		Vector2 mouseDelta = {};
		SDL_Event evt;

		while (SDL_PollEvent(&evt))
		{
			switch (evt.type)
			{

			case SDL_MOUSEBUTTONDOWN:
				if (evt.button.button == SDL_BUTTON_LEFT)
				{
					dragging = true;
					lastPos  = {(f32)evt.motion.x, (f32)evt.motion.y};
				}
				break;
			case SDL_MOUSEBUTTONUP:
				if (evt.button.button == SDL_BUTTON_LEFT)
				{
					dragging = false;
				}
				break;
			case SDL_MOUSEMOTION:
				if (dragging)
				{
					Vector2 curPos = {(f32)evt.motion.x, (f32)evt.motion.y};
					mouseDelta     = curPos - lastPos;
					lastPos        = curPos;
				}
				break;

			case SDL_MOUSEWHEEL:
			{
				z -= evt.wheel.y / 3.0f;
				z = clamp(1.0f, 50.0f, z);
				break;
			}
			case SDL_QUIT:
				running = false;
				break;
			}
		}

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		x -= mouseDelta.x / 3.0f;
		y += mouseDelta.y / 3.0f;

		y = clamp(-89.9f, 89.9f, y);

		Quaternion rot = quatFromAxisAngle(Degree(x), {0, 1, 0}) *
		                 quatFromAxisAngle(Degree(y), {0, 0, 1});

		Vector4 pos = rot.getRotationMatrix() * Vector4(z, 0, 0, 1);
		g_camera.transform.setPosition(Vector3(pos.x, pos.y, pos.z));


		Matrix4 view = lookAt(g_camera.transform.getPosition(),
		                      Vector3(0, 0, 0),
		                      Vector3(0, 1, 0));
		/*	 Matrix4 view = lookAt(g_camera.transform.getPosition(),
		     g_camera.transform.getPosition()+g_camera.transform.getForward(),
		     Vector3(0, 1, 0));*/

		g_particleSystem.update();

		Matrix4 proj = perspective(70, g_width / (float)g_height, 0.01, 1000);

		g_cubeTransform.setPosition(0, 0.0, sin(SDL_GetTicks() / 500.0));
		g_cubeTransform.setRotation(Quaternion::fromAxisAngle(
		    Degree(SDL_GetTicks() / 20.0), g_cubeTransform.getRight()));

		// Quaternion rotation = Quaternion::fromAxisAngle(Degree(SDL_GetTicks()
		// / 20.0), { 0,1,0 });
		// Matrix4 model = translate(0, 0.0, sin(SDL_GetTicks() /
		// 500.0))*rotation.getRotationMatrix();

		Matrix4 model = g_cubeTransform.getMatrix();

		//*  rotate(Degree(SDL_GetTicks() / 20.0), Vector3(1, 1, 0));

		g_particleSystem.render(view, proj);

		g_shaders["default"].use();
		g_textures["Box"].bind();

		g_shaders["default"]
		    .setUniform("tex", 0)
		    .setUniform("u_model", model)
		    .setUniform("u_proj", proj)
		    .setUniform("u_view", view);

		glBindVertexArray(g_cube.vao);

		glDrawElements(
		    g_cube.drawMode, g_cube.vertexCount, GL_UNSIGNED_SHORT, 0);

		g_shaders["default"].setUniform("u_model", Matrix4::Identity);

		glBindVertexArray(g_grid.vao);
		glDrawElements(
		    g_grid.drawMode, g_grid.vertexCount, GL_UNSIGNED_SHORT, 0);

		g_fontRenderer.renderText(
		    "Teaser Engine", {10, (float)(g_height - 60)}, 1, {1, 1, 1, 1});

		SDL_GL_SwapWindow(window);
	}

	SDL_DestroyWindow(window);
	SDL_Quit();
}
