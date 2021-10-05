#include <iostream>
#include <string>
#include "../Physic/Particule.h"
#include "../GUI/GUIBase.h"
#include "../PhysicWorld/PhysicWorld.h"
#ifndef DEF_GAMEBASE
#define DEF_GAMEBASE


class GameBase{

protected :
	std::string name;
	std::string description;
	
	GUIBase guiBase;
	PhysicWorld pW;


public :
	GameBase();
	GameBase(std::string nameGame, std::string descriptionGame);
	~GameBase();
	std::string getName();
	std::string getDescription();
	
	void bouclePrincipale();


	
};
	



#endif