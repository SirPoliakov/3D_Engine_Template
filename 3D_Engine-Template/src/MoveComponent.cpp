#include "MoveComponent.h"
#include "Maths.h"
#include "Actor.h"
#include "Window.h"

MoveComponent::MoveComponent(Actor* ownerP, int updateOrderP)
	: Component(ownerP, updateOrderP), velocity(Vector3::zero), angularSpeed(0.0f)
{
}

void MoveComponent::setVelocity(Vector3 _velocity)
{
	velocity = _velocity;
}

void MoveComponent::setAngularSpeed(float _angularSpeed)
{
	angularSpeed = _angularSpeed;
}

void MoveComponent::update(float dt)
{	
	if (!Maths::nearZero(angularSpeed))
	{
		Quaternion newRotation = owner.getRotation();
		float angle = angularSpeed * dt;
		Quaternion increment(Vector3::unitZ, angle);
		newRotation = Quaternion::concatenate(newRotation, increment);
		owner.setRotation(newRotation);
	}
	if (!Maths::nearZero(velocity.length()))
	{
		Vector3 newPosition = owner.getPosition() + velocity * dt;
		owner.setPosition(newPosition);
	}
}
