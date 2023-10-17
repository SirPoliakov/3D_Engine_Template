#include "Camera.h"
#include "MoveComponent.h"
#include "Game.h"

Camera::Camera() : Actor(), moveComponent(nullptr)
{
	moveComponent = new MoveComponent(this);
}

void Camera::updateActor(float deltaTime)
{
	Actor::updateActor(deltaTime);

	// Compute new camera from this actor
	Vector3 cameraPos = getPosition();
	Vector3 target = getPosition() + getForward() * 600.0f;
	Vector3 up = Vector3::unitZ;

	Matrix4 view = Matrix4::createLookAt(cameraPos, target, up);
	getGame().getRenderer().setViewMatrix(view);
}

void Camera::actorInput(const struct InputState& inputState)
{
	Vector3 vel = Vector3::zero;
	float angSpeed = 0.0f;

	// MOVEMENTS
	if (inputState.keyboard.getKeyValue(SDL_SCANCODE_W))
	{
		vel.x += 300.0;
	}
	if (inputState.keyboard.getKeyValue(SDL_SCANCODE_S))
	{
		vel.x -= 300.0f;
	}
	if (inputState.keyboard.getKeyValue(SDL_SCANCODE_A))
	{
		vel.y -= 180.0f;
	}
	if (inputState.keyboard.getKeyValue(SDL_SCANCODE_D))
	{
		vel.y += 180.0f;
	}


	// ROTATIONS
	/*if (inputState.keyboard.getKeyValue(SDL_SCANCODE_))
	{
		angSpeed.x -= Maths::twoPi;
		angSpeed.y = 0;
	}*/

	moveComponent->setVelocity(vel);
	moveComponent->setAngularSpeed(angSpeed);
}
