//------------------------------------------------------------
// <copyright file="Main.cpp" autor="Markus Perz">
//     Copyright (c) Markus Perz. All rights reserved.
// </copyright>
//------------------------------------------------------------

#include <Teaser/Common.hpp>
#include <Teaser/Graphics.hpp>
#include <Teaser/Graphics/LineRenderer.hpp>
#include <Teaser/Math.hpp>
#include <Teaser/Resources.hpp>
#include <Teaser/Transform.hpp>
#include <Teaser/GameObjects.hpp>
#include <Teaser/Global.hpp>
#include <Teaser/Window.hpp>
#include <Teaser/Time.hpp>
#include <Teaser/Input.hpp>

#include <SOIL/SOIL.h>
#include <iostream>
#include <vector>

using namespace std;
using namespace Teaser;

static int g_width  = 1260;
static int g_height = 870;

static FontRenderer g_fontRenderer;
static SpriteRenderer g_spriteRenderer;
static LineRenderer g_lineRenderer;
static ParticleSystem g_particleSystem;

// static Matrix4 g_camera;
static Transform g_cubeTransform;
static Mesh g_cube;
static Mesh g_grid;


struct Camera
{
	Transform transform;
} g_camera;


Vector2 worldToScreen( const Vector3& world , const Matrix4& projection, const Matrix4& view) 
{
	Vector4 point4d(world[0], world[1], world[2], 1);
	Vector4 inHomo = projection*view*point4d;
	inHomo /= inHomo.w;
	float winX = (((inHomo.x + 1) / 2.0) *  g_width);
	float winY = (((inHomo.y + 1) / 2.0) * g_height);
	return {winX,winY};
}


void initGlobals() 
{
	Global<Window>::setSystem(new Window);
	Global<Time>::setSystem(new Time());
	Global<GOManager>::setSystem(new GOManager());
	Global<Input>::setSystem(new Input());
}

void initGL() 
{
	glClearColor(0.75f, 0.75f, 0.75f, 1.0f);
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LINE_SMOOTH);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glLineWidth(2);
	glViewport(0, 0, g_width, g_height);
}

void shutDownGlobals() 
{
	Global<Input>::shutDown();
	Global<GOManager>::shutDown();
	Global<Window>::shutDown();
	Global<Time>::shutDown();
}

void main()
{

	initGlobals();
	
	Global<Window> window;
	Global<Time> time;
	Global<GOManager> goManager;
	Global<Input> input;

	window->create("Teaser", Window::POSITION_CENTERED, Vec2(g_width,g_height),0);

	g_width = window->getWidth();
	g_height = window->getHeight();


	bool running = true;

	initGL();

	g_textures.insert(Texture::loadTextureFromFile("data/images/cat.png"),
	                  "Cat");
	g_textures.insert(Texture::loadTextureFromFile("data/images/box.png"),
	                  "Box");

	g_shaders.insert(
	    ShaderProgram::loadShaderFromFile("data/shaders/default.vert",
	                                      "data/shaders/default.frag"),
	    "default");

	g_spriteRenderer.init();
	g_fontRenderer.init();
	g_particleSystem.init();
	g_lineRenderer.init();

	g_cube.create(generateCubeData(2.0f));
	g_grid.create(generateGridData(30, 30, 2));

	Vector3 camPos = Vector3(3, 10, 5);

	float x = 0, y = 0;
	float z = 10;

	while (running)
	{
		time->update();

		if (!input->update() || input->getKeyPressed(SDLK_ESCAPE))
			running = false;
		
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		Vector2 mouseDelta = {};

		if (input->getMouseButtonDown(MouseButton::Left)) 
		{
			mouseDelta = input->getDeltaMouse();
		}
			
		z -= input->getMouseWheel() / 3.0f;
		z = clamp(1.0f, 50.0f, z);


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

		g_particleSystem.update();

		Matrix4 proj = perspective(70, g_width / (float)g_height, 0.001, 1000);


		Vector3 trans = Vector3(0, 0.0,cos(SDL_GetTicks() / 1000.0f));
		trans *= Global<Time>::getSystem()->getDeltaTime() * 3.0;
		g_cubeTransform.translate(trans);

		Matrix4 model = g_cubeTransform.getMatrix();

		g_particleSystem.render(view, proj);
		
		g_lineRenderer.setProjectionMatrix(proj);
		g_lineRenderer.setViewMatrix(view);

		g_lineRenderer.renderLine(g_cubeTransform.getPosition(), g_cubeTransform.getRight(), 2 * g_cubeTransform.getScale().x, Vector4(1, 0, 0, 1));
		g_lineRenderer.renderLine(g_cubeTransform.getPosition(), g_cubeTransform.getUp(), 2 * g_cubeTransform.getScale().y, Vector4(0, 1, 0, 1));
		g_lineRenderer.renderLine(g_cubeTransform.getPosition(), g_cubeTransform.getForward(), 2 * g_cubeTransform.getScale().z, Vector4(0, 0, 1, 1));
		
		g_textures["Box"].bind();

		drawMesh(g_shaders["default"], model, view, proj, g_cube);
		drawMesh(g_shaders["default"], Matrix4::Identity, view, proj, g_grid);

		g_fontRenderer.renderText("The Cube", worldToScreen(g_cubeTransform.getPosition()+Vector3(0,1.5,0), proj, view)+Vector2(-20,0), 0.5f, { 0, 0, 0, 1 });

		g_fontRenderer.renderText("Teaser Engine "+ time->deltaTimeToString() , {10, (float)(g_height - 30)}, 0.5f, {0, 0, 0, 1});
		g_fontRenderer.renderText("Time: " + Time::getTimeAsString(), { 10, (float)(g_height - 60) }, 0.5f, { 0.5, 0, 0, 1 });
		g_fontRenderer.renderText("Frames: " + std::to_string(time->getFPS()), { 10, (float)(g_height - 90) }, 0.5f, { 0.5, 0, 0, 1 });
		g_fontRenderer.renderText("MousePos: " + mouseDelta.toString(), { 10, (float)(g_height - 120) }, 0.5f, { 0.5, 0, 0, 1 });

		g_spriteRenderer.render(g_textures["Cat"], 40.0, 20.0, 200, 200, 0);
		

		goManager->cleanUp();
		double dt = time->getDeltaTime();

		goManager->update(dt);
		goManager->draw(dt);

		window->swapBuffers();
	}


	shutDownGlobals();
}
