#pragma once
#include "Component.h"
#include "Vector3.h"

class MoveComponent : public Component
{
public:
	MoveComponent(Actor* ownerP, int updateOrder = 10); // By default, update before other components
	MoveComponent() = delete;
	MoveComponent(const MoveComponent&) = delete;
	MoveComponent& operator=(const MoveComponent&) = delete;

	Vector3 getVelocity() const { return velocity; }
	float getAngularSpeed() const { return angularSpeed; }
	 
	void setVelocity(Vector3 _velocity);
	void setAngularSpeed(float _angularSpeed);

	void update(float dt) override;


private:
	Vector3 velocity;
	float angularSpeed;
};

