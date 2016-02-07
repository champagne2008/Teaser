//------------------------------------------------------------
// <copyright file="Window.cpp" autor="Markus Perz">
//     Copyright (c) Markus Perz. All rights reserved.
// </copyright>
//------------------------------------------------------------

#include <Teaser/Window.hpp>
namespace Teaser
{

	Vec2 Window::POSITION_CENTERED = Vec2(-1,-1);

	Window::Window() 
		:sdlWindow(nullptr)
	{
	
	}

	Window::~Window() 
	{
		SDL_DestroyWindow(sdlWindow);
		SDL_Quit();
	}

	bool Window::create(std::string title, const Vec2& pos, const Vec2& size, unsigned int style)
	{
		SDL_Init(SDL_INIT_EVERYTHING);

		style |= SDL_WINDOW_OPENGL;
		
		int posX = (int)pos.x;
		int posY = (int)pos.y;

		if (posX < 0)
			posX = SDL_WINDOWPOS_CENTERED;
		if (posY < 0)
			posY = SDL_WINDOWPOS_CENTERED;

		sdlWindow = SDL_CreateWindow(title.c_str(), posX, posY, (int)size.x, (int)size.y, style);
		if (sdlWindow == nullptr) 
		{
			fatal("Failed to create a Teaser::Window.");
			return false;
		}
		

		createContext();

		return true;
	}

	bool Window::createContext() 
	{
		SDL_GLContext glContext = SDL_GL_CreateContext(sdlWindow);

		// TODO(Markus): Add better error-checking later
		if (glContext == nullptr)
		{
			fatal("Failed to create an OpenGL Context");
			return false;
		}

		glewExperimental = true;

		if (glewInit() != GLEW_OK)
		{
			fatal("Failed to initialize GLEW!");
			return false;
		}

		return true;
	}

	void Window::setSize(const Vec2& size)
	{
		if (style & Style::RESIZABLE)
		{
			fatal("Trying to resizing an unresizable Window");
			return;
		}

		SDL_SetWindowSize(sdlWindow, size.x, size.y);
	}

    Vec2 Window::getSize()
    {
	    int w, h;
	    SDL_GetWindowSize(sdlWindow, &w, &h);
	    return Vec2(w, h);
    }

    void Window::swapBuffers() 
	{
		SDL_GL_SwapWindow(sdlWindow);
	}

	int Window::getWidth() 
	{
		int w, h;
		SDL_GetWindowSize(sdlWindow, &w, &h);
		return w;
	}

	int Window::getHeight()
	{
		int w, h;
		SDL_GetWindowSize(sdlWindow, &w, &h);
		return h;
	}

} // namespace Teaser