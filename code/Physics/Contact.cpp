//
//  Contact.cpp
//
#include "Contact.h"

/*
====================================================
ResolveContact
====================================================
*/
void ResolveContact( contact_t & contact ) {
	Body *body_a = contact.bodyA;
	Body *body_b = contact.bodyB;

	const float invMassA = body_a->m_invMass;
	const float invMassB = body_b->m_invMass;

	const Vec3 &n = contact.normal;
	const Vec3 &vab = body_a->m_linearVelocity - body_b->m_linearVelocity;
	const float impulse_j = -2.0f * vab.Dot(n) / (invMassA + invMassB);
	const Vec3 vector_impulse_j = n * impulse_j;

	body_a->ApplyImpulseLinear(vector_impulse_j * 1.0f);
	body_b->ApplyImpulseLinear(vector_impulse_j * -1.0f);


	const float tA = body_a->m_invMass / (body_a->m_invMass + body_b->m_invMass);
	const float tB = body_b->m_invMass / (body_a->m_invMass + body_b->m_invMass);
	
	const Vec3 ds = contact.ptOnB_WorldSpace - contact.ptOnA_WorldSpace;
	body_a->m_position += ds * tA;
	body_b->m_position -= ds * tB;
}
