#pragma once

#include "IForce.h"
#include "Particle.h"

class DragForce : public IForce
{
public:
	DragForce(Particle *p, float factor);

	virtual void apply();

	virtual void draw();

	~DragForce(void);

private:
	Particle* m_p;
	float m_factor;

};

