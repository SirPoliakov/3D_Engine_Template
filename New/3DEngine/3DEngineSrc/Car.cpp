#include "Car.h"
#include "MeshComponent.h"
#include "Assets.h"

Car::Car()
{
	MeshComponent* mc = new MeshComponent(this);
	mc->setMesh(Assets::getMesh("Mesh_RacingCar"));
}

void Car::updateActor(float dt)
{
	Vector3 pos = Vector3(0.5, 0, 0);
	setPosition(getPosition() + pos);
}
