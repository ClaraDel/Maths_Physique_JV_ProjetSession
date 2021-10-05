#include <windows.h>
#include<GL/glut.h>
#include "GUIBase.h"

GUIBase* GUIBase::instanceGameBase = nullptr;

GUIBase::GUIBase(){
	X = 0.0;
	Z = 5.0;
	beta = 0;
	angle = 3.14;
	camX = 0.0;
	camZ = 1.0;
	ANG_SPEED = 0.5;
	if (instanceGUIBase == nullptr) {
	instanceGUIBase = this;
	}
	else {
		instanceGUIBase = nullptr;
	}
}

void GUIBase::doKeyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 'esc':
	case 27:
		exit(EXIT_SUCCESS);
	default:
		break;
		
	}
}

void GUIBase::keyboard(unsigned char key, int x, int y) {
	instanceGameBase -> doKeyboard(key, x, y);
}

void GUIBase::doDisplay() {

}

void GUIBase::display() {
	instanceGameBase->doDisplay();
}

//reshape the window
void GUIBase::doReshape(int width, int height) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, width, height);
	gluPerspective(45.0, width * 1.0 / height, 0.1, 100.0);
	glMatrixMode(GL_MODELVIEW);
}

void GUIBase::reshape(int width, int height) {
	instanceGameBase->doReshape(width, height);
}

//rotate the camera with directional keys
void GUIBase::doArrows(int key, int xx, int yy) {
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

void GUIBase::arrows(int key, int xx, int yy) {
	instanceGameBase->doArrows(key, xx, yy);
}

int GUIBase::launch(int argc, char* argv[])
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

	//glutMainLoop();
	return EXIT_SUCCESS;

}
