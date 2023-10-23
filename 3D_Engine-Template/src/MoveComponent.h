#pragma once
#include "Component.h"
#include "Vector3.h"

//const float MAX_GRAV = 100.0f;
//const float GRAV_SCALE = -65.0f;

class MoveComponent : public Component
{
public:
	MoveComponent(Actor* ownerP, int updateOrder = 10); // By default, update before other components
	MoveComponent() = delete;
	MoveComponent(const MoveComponent&) = delete;
	MoveComponent& operator=(const MoveComponent&) = delete;

	float getForwardSpeed() const { return forwardSpeed; }
	float getAngularSpeed() const { return angularSpeed; }
	float getStrafeSpeed() const { return strafeSpeed; }
	 
	void setForwardSpeed(float _forwardSpeed);
	void setAngularSpeed(float _angularSpeed);
	void setStrafeSpeed(float _strafeSpeed);

	//void updateGravity();
	void update(float dt) override;


private:
	float forwardSpeed;
	float angularSpeed;
	float strafeSpeed;
	//float gravityScale;
};

