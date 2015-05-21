#include "DragForce.h"

DragForce::DragForce(Particle *p, float factor) :
	m_p(p), m_factor(factor)
{
}

void DragForce::apply()
{
	m_p -> m_Velocity *= m_factor;
}

void DragForce::draw() {}

DragForce::~DragForce(void)
{
}
