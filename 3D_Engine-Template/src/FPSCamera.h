#pragma once
#include "Actor.h"
#include "CameraComponent.h"
#include "MeshComponent.h"


class FPSCamera : public CameraComponent
{
public:
	FPSCamera(class Actor* owner);

	void update(float dt) override;

	float getPitch() const { return pitch; }
	float getPitchSpeed() const { return pitchSpeed; }
	float getMaxPitch() const { return maxPitch; }

	void setPitchSpeed(float _PitchSpeed);
	void setMaxPitch(float _MaxPitch);

private:
	float pitch;
	float maxPitch;
	float pitchSpeed;
};