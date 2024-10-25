#pragma once
#include "actor.h"
#include "Vector3.h"




class FPSActor : Actor
{
public:
	FPSActor();

	void updateActor(float dt) override;
	void actorInput(const struct InputState& inputState) override;

	void setVisible(bool isVisible);
	void shoot();
	void fixCollisions();


private:
	class MoveComponent* moveComponent;
	class MeshComponent* mesh1Component;
	class FPSCamera* cameraComponent;
	class Actor* FPSModel;
	class BoxComponent* boxComponent;
};

const Vector3 MODEL_OFFSET = Vector3(10.0f, 35.0f, -15.0f);