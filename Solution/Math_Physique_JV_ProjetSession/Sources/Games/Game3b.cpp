#include <iostream>
#include <windows.h>
#include <GL/glut.h>
#include <string>
#include "Game3b.h"
#include <ctime>


#define PI 3.14159265
using namespace std;

Game3b::Game3b(string nameGame, string descriptionGame) : GameBase(nameGame, descriptionGame)
{
	formSize = Vecteur3D();
	rvbColor = Vecteur3D();
	m_registry = RigidBodyForceRegistry();
	rbTabl = vector<RigidBody*>();
	rbChosen = 0;
	X = 0.1;
	Z = 0.0;
	Y = 20.0;
}

//Draw our rigidbody
void Game3b::drawCars(RigidBody* rigidbody) {

	Vecteur3D position;
	position = rigidbody->getPosition();

	glColor3f(rvbColor.getX(), rvbColor.getY(), rvbColor.getZ());
	glPushMatrix();
	glTranslatef(position.getX(), position.getY(), position.getZ());

	glMatrixMode(GL_MODELVIEW);
	//Rotate it with the calculate quaternion
	glRotatef(2 * acos(rigidbody->getOrientation().getW()) * 180.0 / PI, rigidbody->getOrientation().getX(), rigidbody->getOrientation().getY(), rigidbody->getOrientation().getZ());
	glutSolidCube(formSize.getX());
		
	glPopMatrix();

}


void Game3b::doKeyboard(unsigned char key, int x, int y) {

	switch (key) {

	case 32: //space bar
		createCars();
		break;
	case 27: //escape
		exit(EXIT_SUCCESS);
	default:
		break;
	}
}


void Game3b::createCars() {
	RigidBody* car1;
	RigidBody* car2;

	Vecteur3D position = Vecteur3D(5.0, 0.0, 0.1);
	Vecteur3D position2 = Vecteur3D(-5.0, 0.0, -5.0);
	//the point of the collision 
	contactPoint = Vecteur3D(0.0,0.0,0.0);
	Quaternion q1 = Quaternion(1.0, 0, 0, 0);
	// our second car is rotate  from the start 
	Quaternion q2 = Quaternion(cos(PI/4), 0, 1.0, 0);

	formSize = Vecteur3D(1, 1, 1);
	double masse = 5;
	double dx = formSize.getX();
	double dy = formSize.getY();
	double dz = formSize.getZ();
	double i00 = (1.0 / 12.0) * masse * (dy * dy + dz * dz);
	double i11 = (1.0 / 12.0) * masse * (dx * dx + dz * dz);
	double i22 = (1.0 / 12.0) * masse * (dx * dx + dy * dy);
	//Calculate the Inertia Matrix for a cube 
	Matrix33 Inertia = Matrix33(i00, 0.0, 0.0, 0.0, i11, 0.0, 0.0, 0.0, i22);
	Matrix33 inverseInertia = Inertia.Inverse();

	double speed = 5.0;

	//Create our two cars 
	car1 = new RigidBody(position, Vecteur3D(-speed,0,0), masse, q1, 0.99, Vecteur3D(), 0.99, inverseInertia);
	car2 = new RigidBody(position2, Vecteur3D(speed,0,speed), masse, q2, 0.99, Vecteur3D(), 0.99, inverseInertia);
	rvbColor = Vecteur3D(2.0, 0.5, 1);

	rbTabl.push_back(car1);
	rbTabl.push_back(car2);
	
}

//updates the position, acceleration and speed of 
//each particle in the game in each frame time
void Game3b::doUpdatePhysics() {

	double deltaTime = updateTime();

	m_registry.UpdateForce(deltaTime); //update each force 
	for (int i = 0; i < rbTabl.size(); i++) {
		if (i % 2 == 0)
			// Hardcode for our collision 
			if (rbTabl[i+1]->getPosition().getZ() + 0.5 >= contactPoint.getZ()) {
				if (rbTabl[i]->getPosition().getX() - 0.5 <= contactPoint.getX()) {
					//Apply the collision force 
					double  force = 25 * (1.0 / deltaTime);
					rbTabl[i]->addForceAtBodyPoint(Vecteur3D(force, 0, 0), Vecteur3D(0.3, 0.0, 0.5));
					rbTabl[i + 1]->addForceAtBodyPoint(Vecteur3D(-force, 0, 0), Vecteur3D(0.0, 0.0, -sqrt(2)));
				}
			}

		//calculates with respect to the position and speed of the previous frame 
		rbTabl[i]->integrate(deltaTime);
	}

	glutPostRedisplay();
}

//overload of the glut method "glutDisplayFunc. 
//Is executed at each frame
void Game3b::doDisplay() {
	//clear buffer (indicate the buffer to clear)
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//replaces the current matrix with the identity matrix
	glLoadIdentity();

	//specifies the position of the eye point, the reference point
	//and the direction of the up vector
	gluLookAt(X, Y, Z, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	//apply the fonction updatePhysics
	glutIdleFunc(updatePhysics);

	//Draw ground
	glColor3f(0.5, 0.5, 0.5); //gray
	glBegin(GL_QUADS);
	glVertex3f(-10, 0.0, -10);
	glVertex3f(-10, 0.0, 10);
	glVertex3f(10, 0.0, 10);
	glVertex3f(10, 0.0, -10);
	
	
	glEnd();

	for (int i = 0; i < rbTabl.size(); i++) {
		// draw each rigidbody contain in the rigidbody board
		drawCars(rbTabl[i]);
	}

	// swaps the buffers of the current window if double buffered
	glutSwapBuffers();

	glClearColor(0.0f, 0.1f, 0.1f, 1.0f);//background color 
	glEnable(GL_DEPTH_TEST);

}


int Game3b::launch(int argc, char* argv[])
{
	//initialization of glut
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(1280, 720);
	glutCreateWindow("OMG a car accident !!");

	//give to glut our function for display, reshape, keyboard input and arrows management
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(arrows);

	glutMainLoop();
	return EXIT_SUCCESS;

}