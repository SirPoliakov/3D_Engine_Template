#include "Plane.h"

Plane::Plane(const Vector3& normalP, float dP) : normal(normalP), d(dP)
{
}

Plane::Plane(const Vector3& a, const Vector3& b, const Vector3& c)
{
	Vector3 ab = b - a;
	Vector3 ac = c - a;
	normal = Vector3::cross(ab, ac);
	normal.normalize();

	// Equation dans plan :
	
	//						DOT(P,N) + d = 0   <==>   d = (-1) x DOT(P,N)

	//  --> DOT(A,B) est le produit scalaire entre un vecteur A et un 
	//		vecteur B de même dimension (2x2, 3x3, ... nxn), ici 3x3.
	
	//  --> P = (a,b,c) est un point du plan.
	
	//  --> N = (n1, n2, n3) est la normale au plan.
	
	//  --> d la distance (en float) entre l'origine et le point du plan 
	//      le plus proche, autrement dit la distance à l'origine la plus 
	//		courte du plan

	d = -Vector3::dot(a, normal);
}

float Plane::signedDist(const Vector3 point) const
{
	return Vector3::dot(point, normal) - d;
}
