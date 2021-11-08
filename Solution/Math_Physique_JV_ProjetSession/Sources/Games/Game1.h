#pragma once
#include <iostream>
#include <string>
#include "GameBase.h"
#include "../Physic/Particule.h"
#include "../Physic/ForceGenerator/Particle/ParticleGravity.h"
#include "../Physic/ForceGenerator/Particle/ParticleForceRegistry.h"
#ifndef DEF_GAME1
#define DEF_GAME1
#include<vector>

class Game1 : public GameBase {
private : 

	//PARTICULE'S ATTRIBUTES
	int projectileChosen = 0; //type of projectile chosen
	int shapeOfRb = 0;// 0 -> Sphere, 1-> Cube, 2->Torus, 3-> Teapot,4->ellipse 3D
	Vecteur3D rvbColor; //Particule color 
	Vecteur3D formSize; //vector that contains information about particle's shape 


	std::vector<Particule*> partTabl;
	ParticleForceRegistry m_registry;

public : 
	Game1(std::string nameGame, std::string descriptionGame);
	
	void drawParticule(Particule* particule);
	void launchParticule();
	void doUpdatePhysics() override;
 
	int launch(int argc, char* argv[]) override;
	void doKeyboard(unsigned char key, int x, int y) override;
	void doDisplay() override;
};



#endif
