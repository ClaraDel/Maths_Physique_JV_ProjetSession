#include <iostream>
#include <windows.h>
#include <gl/glut.h>
#include <string>
#include "GameBase.h"
#include <ctime>
#include "../Physic/Particule.h"

using namespace std;

static double currentTime = 0;
static double lastTime = 0;

GameBase::GameBase(){}
GameBase::GameBase(string nameGame, string descriptionGame):name(nameGame), description(descriptionGame){}


string GameBase::getName() {
	return name;
}

string GameBase::getDescription() {
	return description;
}

void GameBase::drawParticule(Particule* particule) { //gamebase et spécifier dans game1
}
void keyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 'esc':
	case 27:
		exit(EXIT_SUCCESS);
	default:
		break;
		
	}
}

void GameBase::updatePhysics(Particule* particule) {
	float duration = (float)30 * 0.001;
	if (duration <= 0.0f) return;
	particule->integrate(duration);

	glutPostRedisplay();
}



double GameBase::updateTime(double lastTime) {
	//UPDATE le temps 
	//A FAIRE MARCHER
	lastTime = currentTime;
	currentTime = glutGet(GLUT_ELAPSED_TIME); //getTime();
	double detaTime = (currentTime - lastTime);
	return detaTime;
}

void display() {

}


void reshape(int width, int height) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, width, height);
	gluPerspective(45.0, width * 1.0 / height, 0.1, 100.0);
	glMatrixMode(GL_MODELVIEW);
}


int GameBase::launch()
{
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);

	glutMainLoop();
	return EXIT_SUCCESS;

}



