#pragma once
#include <iostream>
#include <string>
#include "GameBase.h"
#include "../Physic/Particule.h"
#include "../Physic/ForceGenerator/ParticleForceGenerator.h"
#include "../Physic/ForceGenerator/ParticleForceRegistry.h"
#include "../Physic/ForceGenerator/ParticleGravity.h"
#include "../Physic/ForceGenerator/ParticleSpring.h"
#include "../Physic/ForceGenerator/ConstantForce.h"
#ifndef DEF_GAME2
#define DEF_GAME2
#include<vector>

class Game2 : GameBase {

private :
	int m_nbParticules;
	ParticleForceRegistry m_registry;
	std::vector<Particule*> m_blob;


public :
	Game2(std::string nameGame, std::string descriptionGame);

	void createBlob();

	void drawParticule(Particule *particule);
	void launchParticule();
	void doUpdatePhysics() override;

	int launch(int argc, char* argv[]) override;
	void doKeyboard(unsigned char key, int x, int y) override;
	void doDisplay() override;


};

#endif