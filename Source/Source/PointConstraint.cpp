#include "PointConstraint.h"


PointConstraint::PointConstraint(Particle *p, Vec2f position) :
	m_p(p), m_position(position)
{
	particles.push_back(p);
}

float PointConstraint::getC() {
	return (m_p -> m_Position - m_position) * (m_p -> m_Position - m_position);
}

float PointConstraint::getCdot() {
	return (2 * (m_p -> m_Position - m_position)) * m_p -> m_Velocity;
}

std::vector<Vec2f> PointConstraint::getJ() {
	std::vector<Vec2f> j;
	j.push_back(2 * (m_p -> m_Position - m_position));
	j.push_back(2 * (m_position - m_p -> m_Position));
	return j;
}

std::vector<Vec2f> PointConstraint::getJdot() {
	std::vector<Vec2f> jdot;
	jdot.push_back(m_p -> m_Velocity);
	jdot.push_back(-1 * m_p -> m_Velocity);
	return jdot;
}

void PointConstraint::draw()
{
	glBegin( GL_TRIANGLES );
	glColor3f(0.8, 0.7, 0.6);
	glVertex2f(0, 0);
	glVertex2f(1, 0);
	glVertex2f(1, 1);
	glEnd();


	/*
	glBegin( GL_POINT );
	glColor3f(0.8, 0.7, 0.6);
	glVertex2f( m_position[0], m_position[1] );
	glEnd();
	*/
}

PointConstraint::~PointConstraint(void)
{
}
