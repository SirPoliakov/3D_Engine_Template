#include "FPSActor.h"
#include "MoveComponent.h"
#include "Game.h"
#include "MeshComponent.h"
#include "FPSCamera.h"
#include "BallActor.h"
#include "Assets.h"
#include "BoxComponent.h"
#include "Collisions.h"

FPSActor::FPSActor() :
	Actor(),
	moveComponent(nullptr),
	mesh1Component(nullptr),
	cameraComponent(nullptr),
	boxComponent(nullptr)
{
	moveComponent = new MoveComponent(this);
	cameraComponent = new FPSCamera(this);

	FPSModel = new Actor();
	FPSModel->setScale(0.75f);
	mesh1Component = new MeshComponent(FPSModel);
	mesh1Component->setMesh(Assets::getMesh("Mesh_Rifle"));

	boxComponent = new BoxComponent(this);
	AABB collision(Vector3(-25.0f, -25.0f, -87.5f), Vector3(25.0f, 25.0f, 87.5f));
	boxComponent->setObjectBox(collision);
	boxComponent->setShouldRotate(false);
}

void FPSActor::updateActor(float dt)
{
	Actor::updateActor(dt);

	// Update position and rotation of model relatively to position:
	// Position of the FPSmodel:
	// --> set the forward offset and right offset
	Vector3 modelPosition = getPosition();
	modelPosition += getForward() * MODEL_OFFSET.x;
	modelPosition += getRight() * MODEL_OFFSET.y;
	modelPosition.z = MODEL_OFFSET.z;
	FPSModel->setPosition(modelPosition);

	// Rotation of the FPS model:
	// --> Create and set a quaternion q with the right vector and the pitch of the cam  
	Quaternion q = getRotation();
	q = Quaternion::concatenate(q, Quaternion(getRight(), cameraComponent->getPitch()));
	FPSModel->setRotation(q);
	fixCollisions();
}

void FPSActor::actorInput(const InputState& inputState)
{
	// wasd movement
	float forwardSpeed = 0.0f;
	float strafeSpeed = 0.0;
	if (inputState.keyboard.getKeyValue(SDL_SCANCODE_W))
	{
		forwardSpeed += 400.0f;
	}
	if (inputState.keyboard.getKeyValue(SDL_SCANCODE_S))
	{
		forwardSpeed -= 400.0f;
	}
	if (inputState.keyboard.getKeyValue(SDL_SCANCODE_A))
	{
		strafeSpeed -= 400.0f;
	}
	if (inputState.keyboard.getKeyValue(SDL_SCANCODE_D))
	{
		strafeSpeed += 400.0f;
	}

	moveComponent->setForwardSpeed(forwardSpeed);
	moveComponent->setStrafeSpeed(strafeSpeed);


	// Mouse mouvement with x and y cursor position
	// --> set and transfer to moveComp the angular
	Vector2 mousePosition = inputState.mouseState.getPosition();
	float x = mousePosition.x;
	float y = mousePosition.y;

	const int mouseMaxSpeed = 500;
	const float maxAngularSpeed = Maths::pi * 8;
	float angularSpeed = 0.0f;

	if (x != 0)
	{
		angularSpeed = x / mouseMaxSpeed;
		angularSpeed *= maxAngularSpeed;
	}
	moveComponent->setAngularSpeed(angularSpeed);

	// --> set and transfer to CameraComp the pitchSpeed
	const float maxPitchSpeed = Maths::pi * 8;
	float pitchSpeed = 0.0f;
	if (y != 0)
	{
		pitchSpeed = y / mouseMaxSpeed;
		pitchSpeed *= maxPitchSpeed;
	}
	cameraComponent->setPitchSpeed(pitchSpeed);

	// Shoot
	if (inputState.mouseState.getButtonState(1) == ButtonState::Pressed)
	{
		shoot();
	}

}

void FPSActor::setVisible(bool isVisible)
{
	mesh1Component->setVisible(isVisible);
}

void FPSActor::shoot()
{

	// Get start point (in center of screen on near plane)
	Vector3 screenPoint(0.0f, 0.0f, 0.0f);
	Vector3 start = getGame().getRenderer().unproject(screenPoint);

	// Get end point (in center of screen, between near and far)
	screenPoint.z = 0.9f;
	Vector3 end = getGame().getRenderer().unproject(screenPoint);

	// Get direction vector
	Vector3 dir = end - start;
	dir.normalize();

	// Spawn a ball
	BallActor* ball = new BallActor();
	ball->setPlayer(this);
	ball->setPosition(start + dir * 20.0f);

	// Rotate the ball to face new direction
	ball->rotateToNewForward(dir);
}

void FPSActor::fixCollisions()
{
	// Need to recompute world transform to update world box
	computeWorldTransform();
	const AABB& playerBox = boxComponent->getWorldBox();
	Vector3 pos = getPosition();
	auto& planes = getGame().getPlanes();
	for (auto pa : planes)
	{
		// Do we collide with this PlaneActor?
		const AABB& planeBox = pa->getBox()->getWorldBox();
		if (Collisions::intersect(playerBox, planeBox))
		{
			// Calculate all our differences
			float dx1 = planeBox.max.x - playerBox.min.x;
			float dx2 = planeBox.min.x - playerBox.max.x;
			float dy1 = planeBox.max.y - playerBox.min.y;
			float dy2 = planeBox.min.y - playerBox.max.y;
			float dz1 = planeBox.max.z - playerBox.min.z;
			float dz2 = planeBox.min.z - playerBox.max.z;

			// Set dx to whichever of dx1/dx2 have a lower abs
			float dx = Maths::abs(dx1) < Maths::abs(dx2) ? dx1 : dx2;

			// same for dy
			float dy = Maths::abs(dy1) < Maths::abs(dy2) ? dy1 : dy2;

			// same for dz
			float dz = Maths::abs(dz1) < Maths::abs(dz2) ? dz1 : dz2;

			// Whichever is closest, adjust x/y position
			if (Maths::abs(dx) <= Maths::abs(dy) && Maths::abs(dx) <=
				Maths::abs(dz))
			{
				pos.x += dx;
			}
			else if (Maths::abs(dy) <= Maths::abs(dx) && Maths::abs(dy) <=
				Maths::abs(dz))
			{
				pos.y += dy;
			}
			else
			{
				pos.z += dz;
			}

			// Need to set position and update box component
			setPosition(pos);
			boxComponent->onUpdateWorldTransform();
		}
	}
}
