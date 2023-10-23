#include "CameraComponent.h"
#include "Game.h"

CameraComponent::CameraComponent(class Actor* owner, int updateOrder) : Component(owner, updateOrder)
{
}

void CameraComponent::update(float dt)
{
}

void CameraComponent::setViewMatrix(const Matrix4& view)
{
	Game& game = owner.getGame();
	game.getRenderer().setViewMatrix(view);
}