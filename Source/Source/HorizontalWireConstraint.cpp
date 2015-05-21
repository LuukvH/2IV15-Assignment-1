#include "HorizontalWireConstraint.h"


HorizontalWireConstraint::HorizontalWireConstraint(Particle *p, float height) :
m_p(p), m_height(height) {
	particles.push_back(p);
}

void HorizontalWireConstraint::draw()
{
	glBegin(GL_LINES);
	glColor3f(0, 1, 0);
	glVertex2f(-1, m_height);
	glColor3f(0, 1, 0);
	glVertex2f(1, m_height);
	glEnd();
}

// return the c: C(x, y) = (y - yl)
float HorizontalWireConstraint::getC(){
	return  (m_p -> m_Position[1] - m_height);
}

//from the slides C = 1/2(x.x-1) =  (1/2)x.(1/2)x-(1/2)
//from the slides CDot = (1/2)xDot.(1/2)x + (1/2)x.(1/2)xDot
//our C = (y - yc)
//return the C	Dot: (dx/dy)C(x, y) = (y - yc)dx
//CDot = vy
float HorizontalWireConstraint::getCdot(){
	return (m_p->m_Velocity)[1];
}

std::vector<Vec2f> HorizontalWireConstraint::getJ(){
	//a vector, only 1 now, might implement multiple particles
	std::vector<Vec2f> j;
	j.push_back(Vec2f(0, 1));
	return j;
}

//return JDot, if there are more use same order as particle
std::vector<Vec2f> HorizontalWireConstraint::getJdot(){
	std::vector<Vec2f> jdot;
	jdot.push_back(Vec2f(0, 0));
	return jdot;
}

HorizontalWireConstraint::~HorizontalWireConstraint(void)
{
}
