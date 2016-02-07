//------------------------------------------------------------
// <copyright file="Input.cpp" autor="Markus Perz">
//     Copyright (c) Markus Perz. All rights reserved.
// </copyright>
//------------------------------------------------------------

#include <SDL/SDL.h>
#include <Teaser/Input.hpp>

namespace Teaser
{

Input::Input() 
{
	for (int i = 0; i < MAXKEYS; i++)
	{
		keystates[i] = KeyState::UP;
	}

	for (int i = 0; i < MAXMOUSEBUTTONS; i++)
	{
		mousestates[i] = MouseState::UP;
	}

	mousePosition = {};

}

Input::~Input() {}

bool Input::update()
{
	mouseWheel = 0;

	for (int i = 0; i < MAXKEYS; i++)
	{
		if (keystates[i] == KeyState::PRESSED)
			keystates[i] = KeyState::DOWN;
		else if(keystates[i] == KeyState::RELEASED)
			keystates[i] = KeyState::UP;
	}

	for (int i = 0; i < MAXMOUSEBUTTONS; i++)
	{
		if (mousestates[i] == MouseState::PRESSED)
			mousestates[i] = MouseState::DOWN;
		else if (mousestates[i] == MouseState::RELEASED)
			mousestates[i] = MouseState::UP;
	}

	deltaPosition = Vec2(0);

	SDL_Event evt;

	while (SDL_PollEvent(&evt))
	{
		switch (evt.type)
		{

		case SDL_MOUSEBUTTONDOWN: 
		{
			char button = evt.button.button;
			if (mousestates[button] == MouseState::UP)
				mousestates[button] = MouseState::PRESSED;			
			break;
		}

		case SDL_MOUSEBUTTONUP: 
		{
			char button = evt.button.button;
			if(mousestates[button] == MouseState::DOWN)
				mousestates[button] = MouseState::RELEASED;
			break;

		}
		case SDL_MOUSEMOTION:
		{
			Vec2 lastPosition = mousePosition;
			mousePosition     = {(float)evt.motion.x, (float)evt.motion.y};
			if (firstTime)
			{
				firstTime = false;
			}
			else
			{
				deltaPosition = mousePosition - lastPosition;
			}

			break;
		}
		case SDL_MOUSEWHEEL:
		{
			mouseWheel = evt.wheel.y;
			break;
		}

		case SDL_KEYDOWN:
		{
			KeyCode key = evt.key.keysym.sym;
			if (key >= 0 && key < MAXKEYS && keystates[key] == KeyState::UP)
				keystates[key] = KeyState::PRESSED;
			break;
		}

		case SDL_KEYUP:
		{
			KeyCode key = evt.key.keysym.sym;
			if (key >= 0 && key < MAXKEYS && keystates[key] == KeyState::DOWN)
				keystates[key] = KeyState::RELEASED;
			break;
		}

		case SDL_QUIT:
			//The Game will quit now
			return false;
			break;
		}

	}
	return true;
}

bool Input::getKeyPressed(KeyCode key)const 
{
	return keystates[key] == KeyState::PRESSED;
}

bool Input::getKeyReleased(KeyCode key)const 
{
	return keystates[key] == KeyState::RELEASED;
}

bool Input::getKeyDown(KeyCode key)const 
{
	return keystates[key] == KeyState::DOWN;
}

KeyState Input::getKeyState(KeyCode key) const
{
	return keystates[key];
}


bool Input::getMouseButtonPressed(MouseButton button)const 
{
	return mousestates[(int)button] == MouseState::PRESSED;
}
bool Input::getMouseButtonReleased(MouseButton button)const 
{
	return mousestates[(int)button] == MouseState::RELEASED;
}
bool Input::getMouseButtonDown(MouseButton button)const 
{
	return mousestates[(int)button] == MouseState::DOWN;
}

MouseButton Input::getMouseButtonState(MouseButton button) const 
{
	return (MouseButton)mousestates[(int)button];
}

Vector2 Input::getMousePosition() const { return mousePosition; }

void Input::showCursor(bool show) 
{
	SDL_ShowCursor(show);
}

bool Input::isCursorShown()const 
{
	return SDL_ShowCursor(-1);
}

float Input::getMouseWheel()const
{
	return mouseWheel;
}

Vector2 Input::getDeltaMouse()const 
{ 
	return deltaPosition; 
}

} // namespace Teaser