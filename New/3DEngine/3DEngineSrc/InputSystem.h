#pragma once
#include "KeyboardState.h"
#include "MouseState.h"
#include <SDL_events.h>

enum class ButtonState
{
	None,
	Pressed,
	Released, 
	Held
};

struct InputState
{
	KeyboardState keyboard;
	MouseState mouseState;
};

class InputSystem
{
public:
	InputSystem();

	bool initialize();
	void close();

	const InputState getInputState() const { return inputState; }
	bool processEvent(SDL_Event& event); // Return isRunning status

	bool getIsCursorDisplay() const { return isCursorDisplayed; }
	void setMouseCursor(bool _isCursorDisplayed);
	void setMouseRelativeMode(bool _isMouseRelativeOn);

	void preUpdate();
	void update();


private:
	InputState inputState;
	bool isCursorDisplayed;
};

