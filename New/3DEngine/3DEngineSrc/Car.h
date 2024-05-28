#pragma once
#include "Actor.h"
class Car : public Actor
{
public:
	Car();

	void updateActor(float dt) override;
};