#include <iostream>
#include <windows.h>
#include<GL/glut.h>
#include <string>
#include "Game3a.h"
#include <ctime>

#define ProjectileMax 7
using namespace std;




Game3a::Game3a(string nameGame, string descriptionGame) : GameBase(nameGame, descriptionGame)
{	
	formSize = Vecteur3D();
	rvbColor = Vecteur3D();
	m_registry = ParticleForceRegistry();
	rbTabl = vector<Particule*>();
	rbChosen = 0;
	ang = 35;
}

void Game3a::drawParticule(Particule* particule) {
	Vecteur3D position;
	position = particule->getPosition();

	glColor3f(rvbColor.getX(), rvbColor.getY(), rvbColor.getZ());
	glPushMatrix();
	
	glTranslatef(position.getX(), position.getY(), position.getZ());

	//choose the shape of your particle 
	switch (shapeOfRb) {
	case 1:
		//a cube
		//parameters: size
		
		glMatrixMode(GL_MODELVIEW);
		glRotatef(ang, 1.0, 0.0, 0.0);
		glutSolidCube(formSize.getX());
		
		break;
	case 2:
		//a torus
		glRotatef(45.0, 1.0, 0.0, 0.0);
		//parameters: Inner radius of the torus, Outer radius of the torus, Number of sides for each radial section, 
		//Number of radial divisions for the torus
		glutSolidTorus(formSize.getX(), formSize.getY(), formSize.getZ(), 100);
		break;
	case 3:
		//a teapot
		//parameters: size
		glutSolidTeapot(formSize.getX());
		break;
	default:
		break;
	}
	glPopMatrix();

	//we don't want to store more than 20 particles
	if (rbTabl.size() > 20) {
		rbTabl.erase(rbTabl.begin());
	}
}


void Game3a::doKeyboard(unsigned char key, int x, int y) {

	switch (key) {

	case 97: // 'a' key
		rbChosen = (rbChosen + 1) % ProjectileMax;
		break;
	case 32: //space bar
		createRigidBody();
		break;
	case 27: //escape
		exit(EXIT_SUCCESS);
	default:
		break;
	}
}


void Game3a::createRigidBody() {
	Particule* rb;
	switch (rbChosen) {
	case 0:
		//cube
		rb = new Particule(5, Vecteur3D(0, 1, 2), Vecteur3D(), 0.99);
		shapeOfRb = 1;
		rvbColor = Vecteur3D(2.0, 0.5, 1);
		formSize = Vecteur3D(0.5, 0, 0);
		rbTabl.push_back(rb);
		break;
	default:
		break;
	}
}

//updates the position, acceleration and speed of 
//each particle in the game in each frame time
void Game3a::doUpdatePhysics() {

	double deltaTime = updateTime();

	cout << rbTabl.size() << endl;
	//m_registry.UpdateForce(deltaTime); //update each force 

	
	//rigidbody->integrate(deltaTime); 
	

	m_registry.clear();

	glutPostRedisplay();
}

//overload of the glut method "glutDisplayFunc. 
//Is executed at each frame
void Game3a::doDisplay() {
	//clear buffer (indicate the buffer to clear)
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
	//replaces the current matrix with the identity matrix
	glLoadIdentity(); 

	//specifies the position of the eye point, the reference point
	//and the direction of the up vector
	gluLookAt(X, 1, Z, 0.0, 1.0, 0.0,0.0,1.0, 0.0); 

	// rotate of beta along the axes X
	glRotatef(beta, 1, 0, 0);

	//apply the fonction updatePhysics
	glutIdleFunc(updatePhysics); 

	for (int i = 0; i < rbTabl.size(); i++) {
		// draw each particle contain in the particle board
		cout << rbTabl[i]->getPosition() << endl;
		drawParticule(rbTabl[i]);
	}
	
	// swaps the buffers of the current window if double buffered
	glutSwapBuffers();
	
	glClearColor(0.0f, 0.1f, 0.1f, 1.0f);//background color 
	glEnable(GL_DEPTH_TEST);
	
}


int Game3a::launch(int argc, char* argv[])
{
	//initialization of glut
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(1280, 720);
	glutCreateWindow("Demo of rotation");

	//give to glut our function for display, reshape, keyboard input and arrows management
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(arrows);

	glutMainLoop();
	return EXIT_SUCCESS;

}