#pragma once
#include "Component.h"
#include "Vector2.h"

class MoveComponent : public Component
{
public:
	MoveComponent(Actor* ownerP, int updateOrder = 10); // By default, update before other components
	MoveComponent() = delete;
	MoveComponent(const MoveComponent&) = delete;
	MoveComponent& operator=(const MoveComponent&) = delete;

	float getForwardSpeed() const { return forwardSpeed; }
	Vector2 getAngularSpeed() const { return angularSpeed; }

	void setForwardSpeed(float forwardSpeedP);
	void setAngularSpeed(Vector2 angularSpeedP);

	void update(float dt) override;


private:
	float forwardSpeed;
	Vector2 angularSpeed;
};

