#include <iostream>
#include <windows.h>
#include<GL/glut.h>
#include <string>
#include "Game3a.h"
#include <ctime>

using namespace std;


Game3a::Game3a(string nameGame, string descriptionGame) : GameBase(nameGame, descriptionGame)
{	
	m_registry = ParticleForceRegistry();

}

//updates the position, acceleration and speed of 
//each particle in the game in each frame time
void Game3a::doUpdatePhysics() {

	double deltaTime = updateTime();

	
	m_registry.UpdateForce(deltaTime); //update each force 

	
	//rigidbody->integrate(deltaTime); 
	}

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
	gluLookAt(X, 1.0, Z, X + camX, 1.0, Z + camZ, 0.0, 1.0, 0.0); 

	// rotate of beta along the axes X
	glRotatef(beta, 1, 0, 0);

	//apply the fonction updatePhysics
	glutIdleFunc(updatePhysics); 


	
	// swaps the buffers of the current window if double buffered
	glutSwapBuffers();
	
	glClearColor(0.0f, 0.1f, 0.1f, 1.0f);//background color 
	glEnable(GL_DEPTH_TEST);
	
}


int Game1::launch(int argc, char* argv[])
{
	//initialization of glut
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(1280, 720);
	glutCreateWindow("Launching some projectiles");

	//give to glut our function for display, reshape, keyboard input and arrows management
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(arrows);

	glutMainLoop();
	return EXIT_SUCCESS;

}