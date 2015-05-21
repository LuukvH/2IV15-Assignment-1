#include "Particle.h"
#include "IForce.h"
#include "IConstraint.h"

#include "IntegrationScheme.h"
#include "Euler.h"
#include "MidPoint.h"

#include <vector>

static IntegrationScheme * scheme = new Euler();

void simulation_step( std::vector<Particle*> pVector,  std::vector<IForce*> forces, std::vector<IConstraint*> constraints, float dt )
{
	scheme ->  DerivEval(pVector,  forces, constraints, dt);
}