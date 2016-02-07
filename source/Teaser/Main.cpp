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

static Transform g_cubeTransform;
static Mesh g_cube;
static Mesh g_grid;


Vector2 worldToScreen( const Vector3& world , const Matrix4& projection, const Matrix4& view) 
{
	Global<Window> window;
	Vector4 point4d(world, 1);
	Vector4 inHomo = projection*view*point4d;
	inHomo /= inHomo.w;
	float winX = (((inHomo.x + 1) / 2.0) *  window->getWidth());
	float winY = (((inHomo.y + 1) / 2.0) * window->getHeight());
	return {winX,winY};
}


void initGlobals() 
{
	Global<Window>::setSystem(new Window);
	Global<Time>::setSystem(new Time());
	Global<GOManager>::setSystem(new GOManager());
	Global<Input>::setSystem(new Input());
	Global<FontRenderer>::setSystem(new FontRenderer());
	Global<SpriteRenderer>::setSystem(new SpriteRenderer());
	Global<LineRenderer>::setSystem(new LineRenderer());
}

void shutDownGlobals()
{
	Global<SpriteRenderer>::shutDown();
	Global<LineRenderer>::shutDown();
	Global<FontRenderer>::shutDown();
	Global<Input>::shutDown();
	Global<GOManager>::shutDown();
	Global<Window>::shutDown();
	Global<Time>::shutDown();
}

void initGL() 
{
	Global<Window> window;
	glClearColor(0.75f, 0.75f, 0.75f, 1.0f);
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LINE_SMOOTH);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glLineWidth(2);
	glViewport(0, 0, window->getWidth(), window->getHeight());
}



class MeshDrawer: public Component
{
public:
	MeshDrawer(Mesh mesh, ShaderProgram shader)
		:mesh(mesh),
		shader(shader)
	{
	}

	void start()override 
	{
		Vec2 windowSize = Global<Window>::getSystem()->getSize();
		proj = perspective(70, windowSize.x / (float)windowSize.y, 0.001, 1000);
		texture = *Texture::loadTextureFromFile("data/images/box.png");
	}
	void update(float dt) override
	{
		if (Global<Input>::getSystem()->getKeyPressed(SDLK_h))
			show = !show;
	}
	void draw(float dt) override 
	{
		if (show) {
			Matrix4 view = Camera::active().getView();

			texture.bind();
			drawMesh(shader, gameObject->transform.getMatrix(), view, proj, mesh);

			lineRenderer->setProjectionMatrix(proj);
			lineRenderer->setViewMatrix(view);

			lineRenderer->renderLine(gameObject->transform.getPosition(), gameObject->transform.getRight(), 2 * gameObject->transform.getScale().x, Vector4(1, 0, 0, 1));
			lineRenderer->renderLine(gameObject->transform.getPosition(), gameObject->transform.getUp(), 2 * gameObject->transform.getScale().y, Vector4(0, 1, 0, 1));
			lineRenderer->renderLine(gameObject->transform.getPosition(), gameObject->transform.getForward(), 2 * gameObject->transform.getScale().z, Vector4(0, 0, 1, 1));
		}
	}

	bool show = true;

	Global<LineRenderer> lineRenderer;
	Matrix4 proj;
	Mesh mesh;
	ShaderProgram shader;
	Texture texture;
};


class WASDController : public Component 
{
public:

	WASDController(float speed)
		:speed(speed)
	{
	}

	void update(float dt) 
	{
		Global<Input> input;
		Vec3 trans(0);

		float mov = 0;

		if (input->getKeyDown(SDLK_w))
			mov++;
		if (input->getKeyDown(SDLK_s))
			mov--;
		if (input->getKeyDown(SDLK_a))
			gameObject->transform.rotate(dt, { 0,1,0 });
		if (input->getKeyDown(SDLK_d))
			gameObject->transform.rotate(-dt, { 0,1,0 });


		trans = speed*mov*gameObject->transform.getForward();

		if(trans != Vec3::Zero)
			trans.normalize();

		gameObject->transform.translate(trans*dt*speed);

	}
	float speed;
};


void main()
{

	initGlobals();	
	Global<Window> window;
	Global<Time> time;
	Global<GOManager> goManager;
	Global<Input> input;
	Global<FontRenderer> fontRenderer;
	Global<SpriteRenderer> spriteRenderer;
	Global<LineRenderer> lineRenderer;

	Vec2 windowSize = {1250,720};

	window->create("Teaser", Window::POSITION_CENTERED, windowSize,0);

	windowSize = window->getSize();

	fontRenderer->init();
	spriteRenderer->init();
	lineRenderer->init();

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


	g_cube.create(generateCubeData(2.0f));
	g_grid.create(generateGridData(30, 30, 2));

	GameObject& cam = goManager->createGameObject();
	cam.addComponent<Camera>(70, windowSize.x / (float)windowSize.y, 0.001, 1000).activate();
	cam.addComponent<WASDController>(5);

	GameObject& go = goManager->createGameObject();
	go.addComponent<MeshDrawer>(g_cube, g_shaders["default"]);
	go.addComponent<WASDController>(5);

	while (running)
	{
		time->update();

		if (!input->update() || input->getKeyPressed(SDLK_ESCAPE))
			running = false;
		
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		goManager->cleanUp();
		double dt = time->getDeltaTime();
		goManager->update(dt);
		goManager->draw(dt);

		Matrix4 view = Camera::active().getView();
		Matrix4 proj = Camera::active().getProj();

		drawMesh(g_shaders["default"], Matrix4::Identity, view, proj, g_grid);


		Vec3 cubePos = go.transform.getPosition();
		fontRenderer->renderText("The Cube", worldToScreen(cubePos +Vector3(0,1.5,0), proj, view)+Vector2(-20,0), 0.5f, { 0, 0, 0, 1 });
		fontRenderer->renderText("Teaser Engine "+ time->deltaTimeToString() , {10, (float)(windowSize.y - 30)}, 0.5f, {0, 0, 0, 1});
		fontRenderer->renderText("Time: " + Time::getTimeAsString(), { 10, (float)(windowSize.y - 60) }, 0.5f, { 0.5, 0, 0, 1 });
		fontRenderer->renderText("Frames: " + std::to_string(time->getFPS()), { 10, (float)(windowSize.y - 90) }, 0.5f, { 0.5, 0, 0, 1 });
		spriteRenderer->render(g_textures["Cat"], 40.0, 20.0, 200, 200, 0);

		window->swapBuffers();
	}

	shutDownGlobals();
}
