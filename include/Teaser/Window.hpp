//------------------------------------------------------------
// <copyright file="Window.hpp" autor="Markus Perz">
//     Copyright (c) Markus Perz. All rights reserved.
// </copyright>
//------------------------------------------------------------

#ifndef TEASER_WINDOW_HPP
#define TEASER_WINDOW_HPP

#include <Teaser/Common.hpp>
#include <Teaser/Math.hpp>

namespace Teaser
{
class Window
{
public:
	Window();
	~Window();

	static Vec2 POSITION_CENTERED;

	enum Style: Uint32
	{
		RESIZABLE = SDL_WINDOW_RESIZABLE,
		HIDDEN = SDL_WINDOW_HIDDEN,
		FULLSCREEN = SDL_WINDOW_FULLSCREEN_DESKTOP,
		MINIMIZED = SDL_WINDOW_MINIMIZED,
		MAXIMIZED = SDL_WINDOW_MAXIMIZED
	};

	bool create(std::string title, const Vec2& pos, const Vec2& size, unsigned int style = 0);

	void setMousePosition(Vec2 pos);

	void setSize(const Vec2& size);
	Vec2 getSize();

	void showCursor(bool show);

	void swapBuffers();

	int getWidth();
	int getHeight();

private:

	bool createContext();
	
	SDL_Window* sdlWindow;

	unsigned int style;
};

} // namespace Teaser

#endif // TEASER_WINDOW_HPP