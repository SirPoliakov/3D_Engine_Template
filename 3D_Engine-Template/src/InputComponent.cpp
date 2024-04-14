#include "InputComponent.h"
#include "Vector2.h"
#include <SDL_scancode.h>
#include "InputSystem.h"

InputComponent::InputComponent(Actor* ownerP) :
	MoveComponent(ownerP),
	maxForwardSpeed(100.0f),
	maxAngularSpeed(1.0f),
	forwardKey(SDL_SCANCODE_Z),
	backKey(SDL_SCANCODE_S),
	leftKey(SDL_SCANCODE_Q),
	rightKey(SDL_SCANCODE_D),
	pitchUpKey(SDL_SCANCODE_UP),
	pitchDownKey(SDL_SCANCODE_DOWN),
	clockwiseKey(SDL_SCANCODE_RIGHT),
	counterClockwiseKey(SDL_SCANCODE_LEFT)
{
}

void InputComponent::processInput(const struct InputState& inputState)
{
	float forwardSpeed = 0.0f;
	if (inputState.keyboard.getKeyState(forwardKey) == ButtonState::Held)
	{
		forwardSpeed += maxForwardSpeed;
	}
	if (inputState.keyboard.getKeyState(backKey) == ButtonState::Held)
	{
		forwardSpeed -= maxForwardSpeed;
	}
	setForwardSpeed(forwardSpeed);

	float angularSpeed = 0.0f;
	if (inputState.keyboard.getKeyState(clockwiseKey) == ButtonState::Held)
	{
		angularSpeed -= maxAngularSpeed;
		//setAngularSpeed(Vector2(angularSpeed,0.0f));
	}
	if (inputState.keyboard.getKeyState(counterClockwiseKey) == ButtonState::Held)
	{
		angularSpeed += maxAngularSpeed;
		//setAngularSpeed(Vector2(angularSpeed, 0.0f));
	}
	if (inputState.keyboard.getKeyState(pitchUpKey) == ButtonState::Held)
	{
		angularSpeed -= maxAngularSpeed;
		//setAngularSpeed(Vector2(0.0f, angularSpeed));
	}
	if (inputState.keyboard.getKeyState(pitchDownKey) == ButtonState::Held)
	{
		angularSpeed += maxAngularSpeed;
		//setAngularSpeed(Vector2(0.0f, angularSpeed));;
	}
}

void InputComponent::setMaxForwardSpeed(float maxForwardSpeedP)
{
	maxForwardSpeed = maxForwardSpeedP;
}

void InputComponent::setMaxAngularSpeed(float maxAngularSpeedP)
{
	maxAngularSpeed = maxAngularSpeedP;
}

void InputComponent::setForwardKey(SDL_Scancode key)
{
	forwardKey = key;
}

void InputComponent::setBackKey(SDL_Scancode key)
{
	backKey = key;
}

void InputComponent::setLeftKey(SDL_Scancode key)
{
	leftKey = key;
}

void InputComponent::setRightKey(SDL_Scancode key)
{
	rightKey = key;
}

void InputComponent::setPitchUpKey(SDL_Scancode key)
{
	pitchUpKey = key;
}

void InputComponent::setPitchDownKey(SDL_Scancode key)
{
	pitchDownKey = key;
}

void InputComponent::setClockwiseKey(SDL_Scancode key)
{
	clockwiseKey = key;
}

void InputComponent::setCounterClockwiseKey(SDL_Scancode key)
{
	counterClockwiseKey = key;
}
