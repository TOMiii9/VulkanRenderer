//
//  Intersections.cpp
//
#include "Intersections.h"
#include "GJK.h"

/*
====================================================
Intersect
====================================================
*/
bool Intersect( Body * bodyA, Body * bodyB, contact_t & contact ) {
	contact.bodyA = bodyA;
	contact.bodyB = bodyB;

	Vec3 ab = bodyA->m_position - bodyB->m_position;
	const float length_sqr = ab.GetLengthSqr();

	contact.normal = ab;
	contact.normal.Normalize();

	const ShapeSphere *sphereA = (const ShapeSphere *)bodyA->m_shape;
	const ShapeSphere *sphereB = (const ShapeSphere *)bodyB->m_shape;
	
	contact.ptOnA_WorldSpace = bodyA->m_position + ((contact.normal * -1.f) * sphereA->m_radius); // I think I need to multiply with -1.0
	contact.ptOnB_WorldSpace = bodyB->m_position + (contact.normal * sphereB->m_radius);

	const float radiusAB = sphereA->m_radius + sphereB->m_radius;	

	if (length_sqr <= (radiusAB * radiusAB)) {
		return true;
	}
	return false;
}

/*
====================================================
Intersect
====================================================
*/
bool Intersect( Body * bodyA, Body * bodyB, const float dt, contact_t & contact ) {
	// TODO: Add Code

	return false;
}






















