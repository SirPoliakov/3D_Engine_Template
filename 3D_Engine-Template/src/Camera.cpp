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

void Camera::actorInput(const Uint8* keys)
{
	float forwardSpeed = 0.0f;
	Vector2 angSpeed = Vector2(0.0f, 0.0f);
	//MOVEMENT

	if (keys[SDL_SCANCODE_SPACE])
	{
		forwardSpeed += 300.0f;
	}
	if (keys[SDL_SCANCODE_W])
	{
		angSpeed.y -= Maths::twoPi;
		angSpeed.x = 0;
	}
	if (keys[SDL_SCANCODE_S])
	{
		angSpeed.y += Maths::twoPi;
		angSpeed.x = 0;
	}
	if (keys[SDL_SCANCODE_A])
	{
		angSpeed.x += Maths::twoPi;
		angSpeed.y = 0;
	}
	if (keys[SDL_SCANCODE_D])
	{
		angSpeed.x -= Maths::twoPi;
		angSpeed.y = 0;
	}

	moveComponent->setForwardSpeed(forwardSpeed);
	moveComponent->setAngularSpeed(angSpeed);
}
