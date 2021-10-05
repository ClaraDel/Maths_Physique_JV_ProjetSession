#pragma once
#include <iostream>
#include <string>
#include "GameBase.h"
#include "../Physic/Particule.h"
#ifndef DEF_GAME1
#define DEF_GAME1
#include<vector>

class Game1 : public GameBase {
private : 
	std::vector<Particule> partTabl;
	

public : 
	Game1(std::string nameGame, std::string descriptionGame);
	
	void drawParticule(Particule particule);
	void launchParticule();
	void doUpdatePhysics() override;
 
	int launch(int argc, char* argv[]) override;
	void doKeyboard(unsigned char key, int x, int y) override;
	void doDisplay() override;
};



#endif
