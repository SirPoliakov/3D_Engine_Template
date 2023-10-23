#include "InputSystem.h"
#include <SDL_keyboard.h>
#include <cstring>

InputSystem::InputSystem() : inputState(), isCursorDisplayed(0)
{
}

bool InputSystem::initialize()
{
	// Keyboard
	// Assign current state pointer
	inputState.keyboard.currentState = SDL_GetKeyboardState(nullptr);
	// Clear previous state memory
	memset(inputState.keyboard.previousState, 0, SDL_NUM_SCANCODES);

	// Mouse (just set everything to 0)
	inputState.mouseState.currentButtons = 0;
	inputState.mouseState.previousButtons = 0;

	return true;
}

void InputSystem::close()
{
}

bool InputSystem::processEvent(SDL_Event& event)
{
	bool isRunning = true;
	switch (event.type)
	{
	case SDL_QUIT:
		isRunning = false;
		break;
	case SDL_MOUSEWHEEL:
		inputState.mouseState.scrollWheel = Vector2(
			static_cast<float>(event.wheel.x),
			static_cast<float>(event.wheel.y));
		break;
	default:
		break;
	}

	return isRunning;
}

void InputSystem::setMouseCursor(bool _isCursorDisplayed)
{
	isCursorDisplayed = _isCursorDisplayed;
	if (_isCursorDisplayed)
	{
		SDL_ShowCursor(SDL_TRUE);
	}
	else
	{
		SDL_ShowCursor(SDL_FALSE);
	}
}

void InputSystem::setMouseRelativeMode(bool _isMouseRelativeOn)
{
	SDL_bool set = _isMouseRelativeOn ? SDL_TRUE : SDL_FALSE;
	SDL_SetRelativeMouseMode(set);
	
	inputState.mouseState.isRelativeMode = _isMouseRelativeOn;
}

void InputSystem::preUpdate()
{
	// Copy current state to previous
	// Keyboard
	memcpy(inputState.keyboard.previousState, inputState.keyboard.currentState, SDL_NUM_SCANCODES);
	// Mouse
	inputState.mouseState.previousButtons = inputState.mouseState.currentButtons;
	inputState.mouseState.scrollWheel = Vector2::zero;
	// Controller
}

void InputSystem::update()
{
	// Mouse
	int x = 0, y = 0;
	if (inputState.mouseState.isRelativeMode)
	{
		inputState.mouseState.currentButtons = SDL_GetRelativeMouseState(&x,&y);
	}
	else
	{
		inputState.mouseState.currentButtons = SDL_GetMouseState(&x, &y);
	}

	inputState.mouseState.position.x = static_cast<float>(x);
	inputState.mouseState.position.y = static_cast<float>(y);
}
