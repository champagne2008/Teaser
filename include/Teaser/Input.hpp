//------------------------------------------------------------
// <copyright file="Input.hpp" autor="Markus Perz">
//     Copyright (c) Markus Perz. All rights reserved.
// </copyright>
//------------------------------------------------------------

#ifndef TEASER_INPUT_HPP
#define TEASER_INPUT_HPP

#include <Teaser/Common.hpp>
#include <Teaser/Math.hpp>

#include <array>

namespace Teaser
{

using KeyCode = SDL_Keycode;

enum class MouseButton : int
{
	Left = SDL_BUTTON_LEFT,
	Middle = SDL_BUTTON_MIDDLE,
	Right = SDL_BUTTON_RIGHT,
	X1 = SDL_BUTTON_X1,
	X2 = SDL_BUTTON_X2
};
enum class KeyState : char
{
	UP = 0,
	DOWN = 1,
	PRESSED = 2,
	RELEASED = 4
};

using MouseState = KeyState;

class Input
{

public:

	enum
	{
		MAXKEYS = 512,
		MAXMOUSEBUTTONS = 5
	};

	Input();
	~Input();

	bool getKeyPressed(KeyCode key) const;
	bool getKeyReleased(KeyCode key) const;
	bool getKeyDown(KeyCode key) const;
	KeyState getKeyState(KeyCode key) const;

	bool getMouseButtonPressed(MouseButton button) const;
	bool getMouseButtonReleased(MouseButton button) const;
	bool getMouseButtonDown(MouseButton button) const;
	MouseButton getMouseButtonState(MouseButton button) const;

	Vector2 getMousePosition() const;
	Vector2 getDeltaMouse() const;

	void showCursor(bool show);
	bool isCursorShown() const;

	//Returns false if game SDLquit is called
	bool update();

	float getMouseWheel() const;

private:
	bool firstTime = true;

	float mouseWheel;

	Vector2 mousePosition;
	Vector2 deltaPosition;

	std::array<KeyState, MAXKEYS> keystates;
	std::array<MouseState, MAXMOUSEBUTTONS> mousestates;
};

} // namespace Teaser

#endif // TEASER_INPUT_HPP