// TinkerToy.cpp : Defines the entry point for the console application.
//

#include "Particle.h"
#include "SpringForce.h"
#include "Gravity.h"
#include "RodConstraint.h"
#include "IForce.h"
#include "IConstraint.h"
#include "MouseForce.h"
#include "CircularWireConstraint.h"
#include "HorizontalWireConstraint.h"
#include "DragForce.h"


#include <iostream>
#include <fstream>

using namespace std;

#include <vector>
#include <algorithm> 
#include <stdlib.h>
#include <stdio.h>
#include <glut.h>
#include <string>

/* macros */

/* external definitions (from solver) */
extern void simulation_step(std::vector<Particle*> pVector, std::vector<IForce*> forces, std::vector<IForce*> gravityForces, std::vector<IConstraint*> constraints, float dt);

/* global variables */
static int N;
static float dt, d;
static int dsim;
static int grav;
static int dump_frames;
static int frame_number;

// static Particle *pList;
static std::vector<Particle*> pVector;

static int win_id;
static int win_x, win_y;
static int mouse_down[3];
static int mouse_release[3];
static int mouse_shiftclick[3];
static int omx, omy, mx, my;
static int hmx, hmy;

Vec2f MousePos;
int particleSelected = -1;

static MouseForce *mouseForce;
static std::vector<IForce*> forces;
static std::vector<IForce*> gravityForces;
static std::vector<IForce*> nogravityForces;
static std::vector<IConstraint*> constraints;

// Prototypes
void createCloth();

/*
----------------------------------------------------------------------
free/clear/allocate simulation data
----------------------------------------------------------------------
*/

static void free_data ( void )
{
	pVector.clear();
	forces.clear();
	constraints.clear();
}

static void clear_data ( void )
{
	int ii, size = pVector.size();

	for(ii=0; ii<size; ii++){
		pVector[ii]->reset();
	}
}

static void init_system(void)
{
	const double dist = 0.2;
	const Vec2f center(0.0, 0.0);
	const Vec2f offset(dist, 0.0);

	// Create three particles, attach them to each other, then add a
	// circular wire constraint to the first.

	/*pVector.push_back(new Particle(center + offset));


	/*pVector.push_back(new Particle(center + offset));
	pVector.push_back(new Particle(center + offset + offset + Vec2f(0.1, 0.0)));
	pVector.push_back(new Particle(center + offset + offset + offset));

	pVector.push_back(new Particle(center - 3 * offset ));*/

	//pVector.push_back(new Particle(center + offset));
	//pVector.push_back(new Particle(center + offset + offset + Vec2f(0.1, 0.0)));
	//pVector.push_back(new Particle(Vec2f(0.5, 0)));
	//pVector.push_back(new Particle(Vec2f(0, 1)));


	// You shoud replace these with a vector generalized forces and one of
	// constraints...



	mouseForce = new MouseForce();
	forces.push_back(mouseForce);


	/*
	##gravity
	*/



	for (int p = 0; p < pVector.size(); p++) {
		forces.push_back(new Gravity(pVector[p]));
	}
	
	//forces.push_back( new DragForce(pVector[0], 0.99));
	//forces.push_back( new DragForce(pVector[1], 0.99));
	//forces.push_back( new DragForce(pVector[2], 0.99));

	//constraints.push_back(new CircularWireConstraint (pVector[0], Vec2f(0,0), 0.5));
	//constraints.push_back(new RodConstraint(pVector[0], pVector[1], dist));
	//constraints.push_back(new HorizontalWireConstraint (pVector[2], 1));*/


}

/*
----------------------------------------------------------------------
OpenGL specific drawing routines
----------------------------------------------------------------------
*/

static void pre_display ( void )
{
	glViewport ( 0, 0, win_x, win_y );
	glMatrixMode ( GL_PROJECTION );
	glLoadIdentity ();
	gluOrtho2D ( -1.0, 1.0, -1.0, 1.0 );
	glClearColor ( 0.0f, 0.0f, 0.0f, 1.0f );
	glClear ( GL_COLOR_BUFFER_BIT );
}

static void post_display ( void )
{

	frame_number++;

	glutSwapBuffers ();
}

static void draw_particles ( void )
{
	int size = pVector.size();

	for(int ii=0; ii< size; ii++)
	{
		pVector[ii]->draw();
	}
}

static void draw_forces(void)
{
	for_each(forces.begin(), forces.end(), [](IForce* f)
	{
		f->draw();
	});
}

static void draw_constraints ( void )
{
	int size = constraints.size();

	for(int n=0; n< size; n++)
	{
		constraints[n]->draw();
	}
}

/*
----------------------------------------------------------------------
relates mouse movements to tinker toy construction
----------------------------------------------------------------------
*/

static void get_from_UI ()
{
	int i, j;
	// int size, flag;
	int hi, hj;
	// float x, y;
	if ( !mouse_down[0] && !mouse_down[2] && !mouse_release[0] 
	&& !mouse_shiftclick[0] && !mouse_shiftclick[2] ) return;

	i = (int)((       mx /(float)win_x)*N);
	j = (int)(((win_y-my)/(float)win_y)*N);

	if ( i<1 || i>N || j<1 || j>N ) return;

	if ( mouse_down[0] ) {

	}

	if ( mouse_down[2] ) {
	}

	hi = (int)((       hmx /(float)win_x)*N);
	hj = (int)(((win_y-hmy)/(float)win_y)*N);

	if( mouse_release[0] ) {
	}

	omx = mx;
	omy = my;
}

static void remap_GUI()
{
	int ii, size = pVector.size();
	for(ii=0; ii<size; ii++)
	{
		pVector[ii]->m_Position[0] = pVector[ii]->m_ConstructPos[0];
		pVector[ii]->m_Position[1] = pVector[ii]->m_ConstructPos[1];
	}
}

/*
----------------------------------------------------------------------
GLUT callback routines
----------------------------------------------------------------------
*/

static void key_func ( unsigned char key, int x, int y )
{
	switch ( key )
	{
	case 'c':
	case 'C':
		clear_data ();
		break;

	case 'd':
	case 'D':
		dump_frames = !dump_frames;
		break;

	case 'q':
	case 'g':
	case 'G':
		grav = !grav;
		cout << "turned gravity to " << (grav? "TRUE" : "FALSE") << "\n";
		break;
	case 'Q':
		free_data ();
		exit ( 0 );
		break;

	case ' ':
		dsim = !dsim;
		//put vectors on 0 to restart the simulation
		//for_each(pVector.begin(), pVector.end(), [](Particle* v) {
		//	v->m_Velocity = 0;

		//});
		break;
	}
}

static void mouse_func ( int button, int state, int x, int y )
{
	omx = mx = x;
	omx = my = y;

	if(!mouse_down[0]){hmx=x; hmy=y;}
	if(mouse_down[button]) mouse_release[button] = state == GLUT_UP;
	if(mouse_down[button]) mouse_shiftclick[button] = glutGetModifiers()==GLUT_ACTIVE_SHIFT;
	mouse_down[button] = state == GLUT_DOWN;
}

static void motion_func ( int x, int y )
{
	mx = x;
	my = y;
}

static void reshape_func ( int width, int height )
{
	glutSetWindow ( win_id );
	glutReshapeWindow ( width, height );

	win_x = width;
	win_y = height;
}

/*
----------------------------------------------------------------------
relates mouse movements to tinker toy construction
----------------------------------------------------------------------
*/
static void update_mouse_position(void) {
	int i, j;
	i = (int)((mx / (float)win_x)*N);
	j = (int)(((win_y - my) / (float)win_y)*N);

	float x = i - 32;
	x = (float)(x / 32);

	float y = j - 32;
	y = (float)(y / 32);

	MousePos[0] = x;
	MousePos[1] = y;

	mouseForce -> setMousePosition(MousePos);
}
static bool released = true;
static void get_mouse_pos(void)
{

	if (!mouse_down[0] && !mouse_down[2] && !mouse_release[0]
	&& !mouse_shiftclick[0] && !mouse_shiftclick[2]) return;

	update_mouse_position();

	if (!mouse_down[0]) {
		released = true;
		mouseForce -> setEnabled(false);
	}

	if (mouse_down[2]) {
		mouseForce -> clear();
	}

	if (mouse_down[0] && released)
	{
		int i, size = pVector.size();

		for (i = 0; i<size; i++)
		{	
			Vec2f dist = pVector[i]->m_Position - mouseForce -> getMousePosition();
			float distance = dist * dist;

			if (distance < 0.01)
			{
				released = false;
				mouseForce -> setMousePosition(MousePos);
				mouseForce -> setParticle(pVector[i]);
				mouseForce -> setEnabled(true);
				break;
			}
		}
	}
}

static void idle_func ( void )
{
	if (dsim) simulation_step(pVector, forces, (grav ? gravityForces : nogravityForces), constraints, dt);
	else        {get_from_UI();remap_GUI();}

	get_mouse_pos();
	glutSetWindow ( win_id );
	glutPostRedisplay ();
}

static void display_func ( void )
{
	pre_display ();

	draw_forces();
	draw_constraints();
	draw_particles();

	post_display ();
}


/*
----------------------------------------------------------------------
open_glut_window --- open a glut compatible window and set callbacks
----------------------------------------------------------------------
*/

static void open_glut_window ( void )
{
	glutInitDisplayMode ( GLUT_RGBA | GLUT_DOUBLE );

	glutInitWindowPosition ( 0, 0 );
	glutInitWindowSize ( win_x, win_y );
	win_id = glutCreateWindow ( "Tinkertoys!" );

	glClearColor ( 0.0f, 0.0f, 0.0f, 1.0f );
	glClear ( GL_COLOR_BUFFER_BIT );
	glutSwapBuffers ();
	glClear ( GL_COLOR_BUFFER_BIT );
	glutSwapBuffers ();

	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_POLYGON_SMOOTH);

	pre_display ();

	glutKeyboardFunc ( key_func );
	glutMouseFunc ( mouse_func );
	glutMotionFunc ( motion_func );
	glutReshapeFunc ( reshape_func );
	glutIdleFunc ( idle_func );
	glutDisplayFunc ( display_func );
}


/*
create cloth

Creates a 5x5 grid of cloth
*/
Particle* getParticle(int width, int height, int x, int y) {
	return pVector[y * width + x];
}

void createCircular() {
	const double dist = 0.2;
	const Vec2f center(0.0, 0.0);
	const Vec2f offset(dist, 0.0);

	pVector.push_back(new Particle(center + offset));
	pVector.push_back(new Particle(center + offset + offset + Vec2f(0.1, 0.0)));
	pVector.push_back(new Particle(Vec2f(0.5, 0)));

	mouseForce = new MouseForce();
	forces.push_back(mouseForce);

	for (int p = 0; p < pVector.size(); p++) {
		forces.push_back(new Gravity(pVector[p]));
	}
	
	forces.push_back( new DragForce(pVector[0], 0.99));
	forces.push_back( new DragForce(pVector[1], 0.99));
	forces.push_back( new DragForce(pVector[2], 0.99));

	constraints.push_back(new CircularWireConstraint (pVector[0], Vec2f(0,0), 0.5));
	constraints.push_back(new RodConstraint(pVector[0], pVector[1], dist));
	constraints.push_back(new HorizontalWireConstraint (pVector[2], 1));

}

void createCloth() {
	double ks = 1;
	double kd = 1;

	int width = 6;
	int height = 6;
	double dist = 0.15;

	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {

			// Currently added particle
			Particle* p = new Particle(Vec2f(x * dist, y * -dist));
			pVector.push_back(p);

			if (x > 0) { 
				Particle *p1 = getParticle(width, height, x-1, y);
				forces.push_back(new SpringForce(p, p1, ks, kd));
			}

			if (x > 1) { 
				Particle *p1 = getParticle(width, height, x - 2, y);
				forces.push_back(new SpringForce(p, p1, ks, kd));
			}

			if (y > 0) { 
				Particle *p2 = getParticle(width, height, x, y - 1);
				forces.push_back(new SpringForce(p, p2, ks, kd));
			}

			if (y > 1) { 
				Particle *p2 = getParticle(width, height, x, y - 2);
				forces.push_back(new SpringForce(p, p2, ks, kd));
			}

			if (x > 0 && y > 0) { 
				Particle *p3 = getParticle(width, height, x - 1, y - 1);
				forces.push_back(new SpringForce(p, p3, ks, kd));
			}

			if (x < width - 1 && y > 0) { 
				Particle *p4 = getParticle(width, height, x + 1, y - 1);
				forces.push_back(new SpringForce(p, p4, ks, kd));
			}
		}
	}
}

/*
----------------------------------------------------------------------
main --- main routine
----------------------------------------------------------------------
*/

int main ( int argc, char ** argv )
{
	glutInit ( &argc, argv );

	if ( argc == 1 ) {
		N = 64;
		dt = 0.1f;
		d = 5.f;
		grav = true;
		fprintf ( stderr, "Using defaults : N=%d dt=%g d=%g\n",
			N, dt, d );
	} else {
		N = atoi(argv[1]);
		dt = atof(argv[2]);
		d = atof(argv[3]);
	}

	printf ( "\n\nHow to use this application:\n\n" );
	printf ( "\t Toggle construction/simulation display with the spacebar key\n" );
	printf ( "\t Dump frames by pressing the 'd' key\n" );
	printf ( "\t Quit by pressing the 'q' key\n" );


	dsim = 0;
	dump_frames = 0;
	frame_number = 0;

	//options to specify what you would like to run

	bool valid = false;
	grav = false;

	while (!valid) {

		valid = true; // set valid to true so it breaks out of the loop if nothing changes

		printf("\n");
		printf("\t Which example would you like to see? cloth, angle, circle\n");

		string string = "";
		getline(cin, string); //gets line from console and puts it in variable string

		int option;

		if (string == "cloth") {
			option = 1;
		}
		else if (string == "angle") {
			option = 2;
		}
		else if (string == "circle") {
			option = 3;
		}
		else {
			option = 0;
		}


		switch (option)
		{
		default:
			break;
		case 0:
			// no valid option
			cout << "Sorry but " << string << " is not a valid option.";

			valid = false; // makes sure the loops runs again
			break;
		case 1:
			//option cloth
			printf("Generating the cloth example, please wait.");
			createCloth();
			break;

		case 2:
			//option angle
			printf("Generating the angle example, please wait.");
			break;

		case 3:
			printf("Generating the circle constraint example, please wait.");
			createCircular();
			break;
		}




	}


	init_system();  //general function to create stuff

	win_x = 512;
	win_y = 512;
	open_glut_window ();

	glutMainLoop ();

	exit ( 0 );
}
