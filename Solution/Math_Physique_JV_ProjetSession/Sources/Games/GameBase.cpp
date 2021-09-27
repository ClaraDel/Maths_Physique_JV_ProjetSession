#include <iostream>
#include <windows.h>
#include<GL/glut.h>
#include <string>
#include "GameBase.h"
#include <ctime>
#include "../Physic/Particule.h"

using namespace std;

GameBase* GameBase::instanceGameBase = nullptr;

GameBase::GameBase(){
	name = "GameBase";
	description = "Common game base with all games";
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

GameBase::GameBase(string nameGame, string descriptionGame){
	name = nameGame;
	description = descriptionGame;
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

void GameBase::drawParticule(Particule particule) { 
}

double GameBase::updateTime() {
	static double current_time = 0;
	static double last_time = 0;

	last_time = current_time;
	current_time = glutGet(GLUT_ELAPSED_TIME);
	//calculates the time spent between two frames 
	double deltaTime = (current_time - last_time) * 0.001; 
	return deltaTime;
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

void GameBase::updatePhysics2() {
}


void GameBase::updatePhysics() {
	instanceGameBase -> updatePhysics2();
}

void GameBase::display2() {

}

void GameBase::display() {
	instanceGameBase -> display2();
}

//reshape the window
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

//rotate the camera with directional keys
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
	//initialization of glut
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(1280, 720);
	glutCreateWindow("Game");

	//give to glut our function for display, reshape, keyboard input and arrows management
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(arrows);

	glutMainLoop();
	return EXIT_SUCCESS;

}



