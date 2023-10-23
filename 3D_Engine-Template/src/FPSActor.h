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


private:
	class MoveComponent* moveComponent;
	class MeshComponent* meshComponent;
	class FPSCamera* cameraComponent;
	class Actor* FPSModel;
};

const Vector3 MODEL_OFFSET = Vector3(10.0f, 10.0f, -10.0f);