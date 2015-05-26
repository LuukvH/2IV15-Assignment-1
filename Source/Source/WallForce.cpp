#include "WallForce.h"
#include <iostream>
using namespace std;

WallForce::WallForce(Particle *p1) : m_p1(p1) {
	particles.push_back(p1);
}


void WallForce::apply()
{
	//check if the particle goes beyond the border
	//if ()
	m_p1->m_Force -= f; //this moves point 1
}

void WallForce::draw()
{
	// Draw forces
	glBegin(GL_LINES);
	glColor3f(0.6, 0.2, 0.8);
	glVertex2f(m_p1->m_Position[0], m_p1->m_Position[1]);
	glEnd();
}
