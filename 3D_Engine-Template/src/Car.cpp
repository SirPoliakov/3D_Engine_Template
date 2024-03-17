#include "Car.h"
#include "MeshComponent.h"
#include "Assets.h"

Car::Car()
{
	MeshComponent* mc = new MeshComponent(this);
	mc->setMesh(Assets::getMesh("Mesh_RacingCar"));
}
