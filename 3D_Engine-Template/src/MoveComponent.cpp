#include "MoveComponent.h"
#include "Maths.h"
#include "Actor.h"
#include "Window.h"

MoveComponent::MoveComponent(Actor* ownerP, int updateOrderP)
	: Component(ownerP, updateOrderP), forwardSpeed(0.0f), angularSpeed(Vector2::zero)
{

}

void MoveComponent::setForwardSpeed(float forwardSpeedP)
{
	forwardSpeed = forwardSpeedP;
}

void MoveComponent::setAngularSpeed(Vector2 angularSpeedP)
{
	angularSpeed = angularSpeedP;
}

void MoveComponent::update(float dt)
{	
	
	Vector2 angle = angularSpeed * dt;
	if (!Maths::nearZero(angularSpeed.x))
	{	
		Quaternion newRotationX = owner.getRotation();
		Quaternion incrementX(Vector3::unitX, angle.x);
		newRotationX = Quaternion::concatenate(newRotationX, incrementX);
		owner.setRotation(newRotationX);
	}else
	{
		Quaternion newRotationY = owner.getRotation();
		Quaternion incrementY(Vector3::unitY, angle.y);
		newRotationY = Quaternion::concatenate(newRotationY, incrementY);
		owner.setRotation(newRotationY);
	}
	if (!Maths::nearZero(forwardSpeed))
	{
		Vector3 newPosition = owner.getPosition() + owner.getForward() * forwardSpeed * dt;
		owner.setPosition(newPosition);
	}
}
