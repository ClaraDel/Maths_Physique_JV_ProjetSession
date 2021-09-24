#include <iostream>
#include <windows.h>
#include <gl/glut.h>
#include <string>
#include "Game1.h"
#include <ctime>


using namespace std;


Game1::Game1(string nameGame, string descriptionGame) : GameBase(nameGame, descriptionGame)
{

}

void keyboard(unsigned char key, int x, int y) {

	switch (key) {
	case 32: //  barre espace
		launchParticule();
		break;
	case 'esc':
	case 27:
		exit(EXIT_SUCCESS);
	default:
		break;
	}
}


void Game1::drawParticule(Particule* particule) { //gamebase et spécifier dans game1
	Vecteur3D position = particule->getPosition();

	glColor3f(0, 0, 0); // black 
	glPushMatrix();
	glTranslatef(position.getX(), position.getY(), position.getZ()); // put the object at his position
	glutSolidSphere(0.3, 10, 10); // object is a sphere 
	glPopMatrix();
}

void Game1::launchParticule() {

	//faire un switch 
	Particule* pointeurTableau = tableauParticule;

	pointeurTableau->setMasse(10);
	pointeurTableau->setVelocity(0, 0, 50);
	pointeurTableau->setAcceleration(0, -2, 0);
	pointeurTableau->setDamping(1);
	pointeurTableau->setPosition(X, 0.75, Z);
}

void Game1::updatePhysics(Particule* particule) {
	float duration = (float)30 * 0.001;
	if (duration <= 0.0f) return;
	particule->integrate(duration);

	glutPostRedisplay();
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	gluLookAt(X, 1.0f, Z, X + camX, 1.0f, Z + camZ, 0.0f, 1.0f, 0.0f);
	glRotatef(beta, 1, 0, 0);

	for (Particule* particule = tableauParticule; particule < tableauParticule + 20; particule++) {
		//calcul temps
		updatePhysics(particule);
		drawParticule(particule);
	}

	glutSwapBuffers();

	glClearColor(0.9f, 0.95f, 1.0f, 1.0f);
	glEnable(GL_DEPTH_TEST);
}

int Game1::launch()
{

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);

	glutMainLoop();
	return EXIT_SUCCESS;

}
