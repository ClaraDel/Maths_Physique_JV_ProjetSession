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


};

#endif
