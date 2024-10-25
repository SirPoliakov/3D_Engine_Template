#pragma once
#include "Vector3.h"
#include "LineSegment.h"
#include <functional>
#include <vector>

using std::vector;

class PhysicsSystem
{
public:
	struct CollisionInfo
	{
		// Point of collision
		Vector3 point;
		// Normal at collision
		Vector3 normal;
		// Component collided with
		class BoxComponent* box;
		// Owning actor of component
		class Actor* actor;
	};
	PhysicsSystem() = default;

	// Add/remove box components from world
	void addBox(class BoxComponent* box);
	void removeBox(class BoxComponent* box);
	bool segmentCast(const LineSegment& l, CollisionInfo& outColl);
	// Test collisions using sweep and prune
	void testSweepAndPrune(std::function<void(class Actor*, class Actor*)> f);

private:
	vector<class BoxComponent*> boxes;
};