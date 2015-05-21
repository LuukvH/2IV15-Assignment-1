#include "MouseForce.h"

MouseForce::MouseForce() :
	m_mouse(new Particle(Vec2f(0, 0))), m_p(new Particle(Vec2f(0, 0))), m_kd(1.0), m_ks(2.0), m_enabled(false)
{	
}

void MouseForce::draw()
{
	m_mouse->draw();

	if (m_enabled) {
		glBegin(GL_LINES);
		glColor3f(1, 1, 0);
		glVertex2f(m_p->m_Position[0], m_p->m_Position[1]);
		glColor3f(1, 1, 0);
		glVertex2f(m_mouse->m_Position[0], m_mouse->m_Position[1]);
		glEnd();
	}
}

void MouseForce::setEnabled(bool enabled)
{
	m_enabled = enabled;
}

void MouseForce::setMousePosition(const Vec2f & mouse)
{
	m_mouse->m_Position = mouse;
}

void MouseForce::setParticle(Particle* p)
{
	m_p = p;
}

void MouseForce::apply()
{
	if (m_enabled) {
		SpringForce springForce = SpringForce::SpringForce(m_p, m_mouse, 0, m_ks, m_kd);
		springForce.apply();
	}
}