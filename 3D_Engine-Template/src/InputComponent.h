#pragma once
#include "MoveComponent.h"
#include <SDL_stdinc.h>
#include <SDL_scancode.h>

class InputComponent : public MoveComponent
{
public:
	InputComponent(Actor* ownerP);
	InputComponent() = delete;
	InputComponent(const InputComponent&) = delete;
	InputComponent& operator=(const InputComponent&) = delete;

	void processInput(const struct InputState& inputState);

	void setMaxVelocity(Vector3 _maxVelocity);
	void setMaxAngularSpeed(float maxAngularSpeedP);
	void setForwardKey(SDL_Scancode key);
	void setBackKey(SDL_Scancode key);
	void setLeftKey(SDL_Scancode key);
	void setRightKey(SDL_Scancode key);
	void setPitchUpKey(SDL_Scancode key);
	void setPitchDownKey(SDL_Scancode key);
	void setClockwiseKey(SDL_Scancode key);
	void setCounterClockwiseKey(SDL_Scancode key);


private:
	float maxVelocityScale;
	float maxAngularSpeed;

	// ZQSD moves
	SDL_Scancode forwardKey;
	SDL_Scancode backKey;
	SDL_Scancode leftKey;
	SDL_Scancode rightKey;

	// UP LEFT DOWN RIGHT Cam
	SDL_Scancode pitchUpKey;
	SDL_Scancode pitchDownKey;
	SDL_Scancode clockwiseKey;
	SDL_Scancode counterClockwiseKey;
};

