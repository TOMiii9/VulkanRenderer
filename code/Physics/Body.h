//
//	Body.h
//
#pragma once
#include "../Math/Vector.h"
#include "../Math/Quat.h"
#include "../Math/Matrix.h"
#include "../Math/Bounds.h"
#include "Shapes.h"

#include "../Renderer/model.h"
#include "../Renderer/shader.h"

/*
====================================================
Body
====================================================
*/
class Body {
public:
	Body();

	Vec3		m_position;
	Quat		m_orientation;
	Vec3		m_linearVelocity;
	float		m_invMass;
	Shape *		m_shape;

	void ApplyImpulseLinear(const Vec3 &impulse);
};
