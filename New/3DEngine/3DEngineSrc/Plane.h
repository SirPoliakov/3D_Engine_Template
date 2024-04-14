#pragma once
#include "Vector3.h"

struct Plane
{
	//Constructor:

	Plane(const Vector3& normalP, float dP);
	Plane(const Vector3& a, const Vector3& b, const Vector3& c);

	float signedDist(const Vector3 point) const;

	float d;
	Vector3 normal;
};