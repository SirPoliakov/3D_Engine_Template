#include "Collisions.h"
#include <algorithm>

bool Collisions::intersect(const Sphere& a, const Sphere& b)
{
    float distSq = (b.center - a.center).lengthSq();
    float sumRad = a.radius + b.radius;
    return distSq <= (sumRad*sumRad);
}

bool Collisions::intersect(const AABB& a, const AABB& b)
{
	bool outside = a.max.x < b.min.x ||
		a.max.y < b.min.y ||
		a.max.z < b.min.z ||
		b.max.x < a.min.x ||
		b.max.y < a.min.y ||
		b.max.z < a.min.z;

	return !outside;
}

bool Collisions::intersect(const Sphere& s, const AABB& box)
{
	float distSq = box.minDistSq(s.center);
	return distSq <= (s.radius * s.radius);
}

bool Collisions::intersect(const LineSegment& l, const Sphere& s, float& outT)
{
	Vector3 X = l.start - s.center;
	Vector3 Y = l.end - l.start;

	float a = Vector3::dot(Y, Y);
	float b = 2 * Vector3::dot(X, Y);
	float c = Vector3::dot(X,X) - (s.radius * s.radius);

	float disc = b * b - 4 * a * c;

	if (disc < 0.0f)
	{
		return false;
	}
	else
	{
		disc = Maths::sqrt(disc);

		float tMin = -b - disc / 2 * a;
		float tMax = -b + disc / 2 * a;

		if (tMin >= 0.0f && tMin <= 1.0f)
		{
			outT = tMin;
			return true;
		}
		else if (tMax >= 0.0f && tMax <= 1.0f)
		{
			outT = tMax;
			return true;
		}
		else return false;
	}
}

bool Collisions::intersect(const LineSegment& l, const Plane& p, float& outT)
{
	// First test if there's a solution for t
	float denom = Vector3::dot(l.end - l.start, p.normal);
	if (Maths::nearZero(denom))
	{
		// The only way they intersect is if start
		// is a point on the plane (P dot N) == d
		if (Maths::nearZero(Vector3::dot(l.start, p.normal) - p.d))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		float numer = -Vector3::dot(l.start, p.normal) - p.d;
		outT = numer / denom;
		// Validate t is within bounds of the line segment
		if (outT >= 0.0f && outT <= 1.0f)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

}

bool Collisions::intersect(const LineSegment& l, const AABB& b, float& outT, Vector3& outNorm)
{
	std::vector<pair<float, Vector3>> tvals;

	// x
	testSidePlane(l.start.x, l.end.x, b.min.x, Vector3::negUnitX, tvals);
	testSidePlane(l.start.x, l.end.x, b.max.x, Vector3::unitX, tvals);

	//y
	testSidePlane(l.start.y, l.end.y, b.min.y, Vector3::negUnitY, tvals);
	testSidePlane(l.start.y, l.end.y, b.max.y, Vector3::unitY, tvals);

	//z
	testSidePlane(l.start.z, l.end.z, b.min.z, Vector3::negUnitZ, tvals);
	testSidePlane(l.start.z, l.end.z, b.max.z, Vector3::unitZ, tvals);

	std::sort(tvals.begin(), tvals.end(), [](
		const std::pair<float, Vector3>& a,
		const std::pair<float, Vector3>& b) 
		{
			return a.first < b.first;
		});
	Vector3 point;

	for (auto& val : tvals)
	{
		point = l.pointOnSegment(val.first); 
		if (b.contains(point))
		{
			outT = val.first;
			outNorm = val.second;

			return true;
		}
	}

	return false;
}

bool Collisions::intersectSlab(const LineSegment& l, const AABB& b, float& outT)
{
	float t0 = 0.0f, t1 = 1.0f;
	float tminX, tmaxX, tminY, tmaxY, tminZ, tmaxZ;

	if(!computeSlab(l.start.x, l.end.x, b.min.x, b.max.x, t0, t1, tminX, tmaxX)) return false;
	if(!computeSlab(l.start.y, l.end.y, b.min.y, b.max.y, t0, t1, tminY, tmaxY)) return false;
	if(!computeSlab(l.start.z, l.end.z, b.min.z, b.max.z, t0, t1, tminZ, tmaxZ)) return false;

	float tMin = std::max({ tminX, tminY, tminZ });
	float tMax = std::min({ tmaxX, tmaxY, tmaxZ });

	if (tMin <= tMax)
	{
		outT = tMin;
		return true;
	}
	else return false;
}

bool Collisions::computeSlab(float start, float end, float boxMin, float boxMax, float& t0, float& t1, float& tmin, float& tmax)
{

	float invD = 1 / (end - start);
	tmin = (boxMin - start) * invD;
	tmax = (boxMax - start) * invD;

	if (tmin > tmax) std::swap(tmin, tmax);

	t0 = std::max(t0, tmin);
	t1 = std::min(t1, tmax);

	return t0 <= t1;
}

bool Collisions::testSidePlane(float start, float end, float negd, const Vector3& norm, vector<pair<float, Vector3>>& out)
{
	float denom = end - start;

	if (Maths::nearZero(denom))
	{
		return false;
	}
	else
	{
		float nume = -start + negd;

		float t = nume / denom;

		if (t >= 0.0f && t <= 1.0f)
		{
			out.emplace_back(t, norm);
			return true;
		}
		else return false;
	}
	
}

bool Collisions::sweptSphere(const Sphere& P0, const Sphere& P1, const Sphere& Q0, const Sphere& Q1, float& outT)
{
	Vector3 u = P1.center - P0.center;
	Vector3 v = Q1.center - Q0.center;
	Vector3 x = u - v;
	Vector3 w = P0.center - Q0.center;

	float sumRadii = P0.radius + Q0.radius;

	float c = Vector3::dot(w, w) - (sumRadii * sumRadii);
	float b = 2 * Vector3::dot(w,x);
	float a = Vector3::dot(x,x);

	float disc = b * b - 4 * a * c;

	if (disc < 0) return false;
	else
	{
		disc = std::sqrt(disc);
		outT = (-b - disc) / 2 * a;
		if (outT >= 0.0f && outT <= 1.0f) return true;
		else return false;
	}
}
