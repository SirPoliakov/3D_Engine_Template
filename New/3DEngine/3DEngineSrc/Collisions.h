#pragma once
#include "Sphere.h"
#include "AABB.h"
#include "LineSegment.h"
#include "Plane.h"
#include <vector>
using std::vector;
using std::pair;

namespace Collisions
{
	// DISCRETE DETECTIONS
	bool intersect(const Sphere& a, const Sphere& b);
	bool intersect(const AABB& a, const AABB& b);
	bool intersect(const Sphere& s, const AABB& box);
	bool intersect(const LineSegment& l, const Sphere& s, float&
		outT);
	bool intersect(const LineSegment& l, const Plane& p, float& outT);
	bool intersect(const LineSegment& l, const AABB& b, float& outT,
		Vector3& outNorm);
	bool intersectSlab(const LineSegment& l, const AABB& b, float& outT);
	bool computeSlab(float start, float end, float boxMin, float boxMax,
		float& t0, float& t1, float& tmin, float& tmax);
	bool testSidePlane(float start, float end, float negd,
		const Vector3& norm, vector<pair<float, Vector3>>& out);

	// CONTINUOUS DETECTIONS
	bool sweptSphere(const Sphere& P0, const Sphere& P1,
		const Sphere& Q0, const Sphere& Q1, float& outT);
}
