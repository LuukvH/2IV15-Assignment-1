#pragma once

#include "Particle.h"
#include "IForce.h"
#include "SpringForce.h"

class MouseForce : public IForce
{
public:
	MouseForce();

	virtual void draw();
	virtual void apply();

	void setMousePosition(const Vec2f & mouse);
	void setEnabled(bool applyForce);

	void setParticle(Particle * p);
private:
	
	Particle * m_p;   // particle 1
	Particle* m_mouse;

	bool m_enabled;
	double  m_ks, m_kd; // spring strength constants
};