#include <iostream>
#include <windows.h>
#include<GL/glut.h>
#include <string>
#include "GameBase.h"
#include <ctime>
#include "../Physic/Particule.h"

using namespace std;

static double currentTime = 0;
static double lastTime = 0;

GameBase* GameBase::instanceGameBase = nullptr;

GameBase::GameBase(){
	name = "";
	description = "";
	X = 0.0;
	Z = 5.0;
	beta = 0;
	angle = 3.14;
	camX = 0.0;
	camZ = 1.0;
	ANG_SPEED = 0.5;
	if (instanceGameBase == nullptr) {
		instanceGameBase = this;
	}
	else {
		instanceGameBase = nullptr;
	}
}

GameBase::GameBase(string nameGame, string descriptionGame):name(nameGame), description(descriptionGame){
	X = 0.0;
	Z = 5.0;
	beta = 0;
	angle = 3.14;
	camX = 0.0;
	camZ = 1.0;
	ANG_SPEED = 0.5;
	if (instanceGameBase == nullptr) {
		instanceGameBase = this;
	}
	else {
		instanceGameBase = nullptr;
	}
}

GameBase::~GameBase() {
	instanceGameBase = nullptr;
}

string GameBase::getName() {
	return name;
}

string GameBase::getDescription() {
	return description;
}

void GameBase::drawParticule(Particule* particule) { //gamebase et spécifier dans game1
}


void GameBase::keyboard2(unsigned char key, int x, int y) {
	switch (key) {
	case 'esc':
	case 27:
		exit(EXIT_SUCCESS);
	default:
		break;
		
	}
}

void GameBase::keyboard(unsigned char key, int x, int y) {
	instanceGameBase -> keyboard2(key, x, y);
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

void GameBase::display2() {

}

void GameBase::display() {
	instanceGameBase -> display2();
}

void GameBase::reshape2(int width, int height) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, width, height);
	gluPerspective(45.0, width * 1.0 / height, 0.1, 100.0);
	glMatrixMode(GL_MODELVIEW);
}

void GameBase::reshape(int width, int height) {
	instanceGameBase->reshape2(width, height);
}

void GameBase::arrows2(int key, int xx, int yy) {
	switch (key) {
	case GLUT_KEY_UP:
		beta += ANG_SPEED;
		break;
	case GLUT_KEY_DOWN:
		beta -= ANG_SPEED;
		break;
	case GLUT_KEY_LEFT:
		angle -= (2 / ANG_SPEED) * (0.01f);
		camX = sin(angle);
		camZ = -cos(angle);
		break;
	case GLUT_KEY_RIGHT:
		angle += (2 / ANG_SPEED) * 0.01f;
		camX = sin(angle);
		camZ = -cos(angle);
		break;
	default:
		break;
	}
}

void GameBase::arrows(int key, int xx, int yy) {
	instanceGameBase->arrows2(key, xx, yy);
}

int GameBase::launch(int argc, char* argv[])
{	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(1280, 720);
	glutCreateWindow("Game");

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);

	glutMainLoop();
	return EXIT_SUCCESS;

}



