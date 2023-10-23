#include "MoveComponent.h"
#include "Maths.h"
#include "Actor.h"
#include "Window.h"

MoveComponent::MoveComponent(Actor* ownerP, int updateOrderP)
	: Component(ownerP, updateOrderP), forwardSpeed(0.0f), angularSpeed(0.0f), strafeSpeed(0.0f)
{
}

void MoveComponent::setForwardSpeed(float _forwardSpeed)
{
	forwardSpeed = _forwardSpeed;
}

void MoveComponent::setAngularSpeed(float _angularSpeed)
{
	angularSpeed = _angularSpeed;
}

void MoveComponent::setStrafeSpeed(float _strafeSpeed)
{
	strafeSpeed = _strafeSpeed;
}

/*void MoveComponent::updateGravity()
{
	float res = velocity.z + gravityScale;
	if (Maths::abs(res) <= MAX_GRAV) velocity.z = res;
	else if(res <0) velocity.z -= MAX_GRAV;
	else velocity.z += MAX_GRAV;
}*/

void MoveComponent::update(float dt)
{	
	if (!Maths::nearZero(angularSpeed))
	{
		Quaternion newRotation = owner.getRotation();
		
		float angle = angularSpeed * dt;
		Quaternion incrementZ(Vector3::unitZ, angle);
		newRotation = Quaternion::concatenate(newRotation, incrementZ);
		owner.setRotation(newRotation);
	}
	//updateGravity();

	if (!Maths::nearZero(forwardSpeed))
	{
		
		Vector3 newPosition = owner.getPosition();
		newPosition += owner.getForward() * forwardSpeed * dt;
		newPosition += owner.getRight() * strafeSpeed * dt;
		owner.setPosition(newPosition);
	}
}
