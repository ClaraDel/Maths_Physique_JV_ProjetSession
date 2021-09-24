#pragma once
#include <iostream>
#include <string>
#include "GameBase.h"
#include "../Physic/Particule.h"
#ifndef DEF_GAME1
#define DEF_GAME1
#include <list>

class Game1 : public GameBase {
private : 
	Particule tableauParticule[20];
	std::list<Particule> listParticule = {};
	double X = 0.0;
	double Z = 5.0;
	//cam direction
	 double beta = 0; //camera along z axis
	 double angle = 3.14;
	// actual vector representing the camera's direction
	double  camX = 0.0, camZ = 1.0;
	double ANG_SPEED = 0.5;

public : 
	Game1(std::string nameGame, std::string descriptionGame);
	
	void drawParticule(Particule* particule);
	void launchParticule();
	void updatePhysics(Particule* particule);
 
	int launch();
};

void keyboard(unsigned char key, int x, int y);
void display();
#endif
