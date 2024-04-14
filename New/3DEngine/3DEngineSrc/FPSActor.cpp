#include "FPSActor.h"
#include "MoveComponent.h"
#include "Game.h"
#include "MeshComponent.h"
#include "FPSCamera.h"
#include "Assets.h"

FPSActor::FPSActor() :
	Actor(),
	moveComponent(nullptr),
	mesh1Component(nullptr),
	cameraComponent(nullptr)
{
	moveComponent = new MoveComponent(this);
	cameraComponent = new FPSCamera(this);

	FPSModel = new Actor();
	FPSModel->setScale(0.75f);
	mesh1Component = new MeshComponent(FPSModel);
	mesh1Component->setMesh(Assets::getMesh("Mesh_Rifle"));
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
}

void FPSActor::setVisible(bool isVisible)
{
	mesh1Component->setVisible(isVisible);
}
