#pragma once
#include <iostream>
#include <string>
#include "../Physic/Particule.h"
#ifndef DEF_GUIBASE
#define DEF_GUIBASE

class GUIBase {
private:
	// Global variables  
	//cam position
	double X, Z;

	//cam position
	double beta; //camera along z axis
	double angle;

	// actual vector representing the camera's direction
	double camX, camZ;

	double ANG_SPEED;


public:
	GUIBase();
	virtual int launch(int argc, char* argv[]);
	void drawParticule(Particule particule);
	static void arrows(int key, int xx, int yy);
	static void display();
	static void keyboard(unsigned char key, int x, int y);
	static void reshape(int width, int height);

	virtual void doArrows(int key, int xx, int yy);
	virtual void doDisplay();
	virtual void doKeyboard(unsigned char key, int x, int y);
	virtual void doReshape(int width, int height);


};

#endif
