#pragma once

#include "Particle.h"
#include "IForce.h"

class WallForce : public IForce
{
public:
	WallForce::WallForce(Particle *p1);

	virtual void apply();

	virtual void draw();

private:

	Particle * const m_p1;   // particle 1
};
