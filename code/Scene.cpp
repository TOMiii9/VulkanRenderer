//
//  Scene.cpp
//
#include "Scene.h"
#include "Physics/Contact.h"
#include "Physics/Intersections.h"
#include "Physics/Broadphase.h"

/*
========================================================================================================

Scene

========================================================================================================
*/

/*
====================================================
Scene::~Scene
====================================================
*/
Scene::~Scene() {
	for ( int i = 0; i < m_bodies.size(); i++ ) {
		delete m_bodies[ i ].m_shape;
	}
	m_bodies.clear();
}

/*
====================================================
Scene::Reset
====================================================
*/
void Scene::Reset() {
	for ( int i = 0; i < m_bodies.size(); i++ ) {
		delete m_bodies[ i ].m_shape;
	}
	m_bodies.clear();

	Initialize();
}

/*
====================================================
Scene::Initialize
====================================================
*/
void Scene::Initialize() {
	Body body;
	body.m_position = Vec3( 0, 0, 10 );
	body.m_orientation = Quat( 0, 0, 0, 1 );
	body.m_shape = new ShapeSphere( 1.0f );
	body.m_invMass = 1.0f;
	m_bodies.push_back( body );

	body.m_position = Vec3( 0, 0, -1000 );
	body.m_orientation = Quat( 0, 0, 0, 1 );
	body.m_shape = new ShapeSphere( 1000.0f );
	body.m_invMass = 0.0f;
	m_bodies.push_back( body );
}

/*
====================================================
Scene::Update
====================================================
*/
void Scene::Update( const float dt_sec ) {
	// accelerate
	for (Body &body : m_bodies) {		
		// gravity -> impulse
		float mass = 10.f / body.m_invMass;
		Vec3 gravity_impulse = Vec3(0,0,-10) * mass * dt_sec;
		body.ApplyImpulseLinear(gravity_impulse);
	}

	for (int i = 0; i < m_bodies.size(); i++ ) {
		for (int j = i + 1; j < m_bodies.size(); j++ ) {
			Body *body_a = &m_bodies[i];
			Body *body_b = &m_bodies[j];

			if (0.0f == body_a->m_invMass && 0.0f == body_b->m_invMass) {
				continue;
			}

			contact_t contact;
			if (Intersect(body_a, body_b, contact)) {
				ResolveContact(contact);
			}
		}
	}

	// update positions
	for (int i = 0; i < m_bodies.size(); i++) {
		m_bodies[i].m_position += m_bodies[i].m_linearVelocity * dt_sec;
	}
}
