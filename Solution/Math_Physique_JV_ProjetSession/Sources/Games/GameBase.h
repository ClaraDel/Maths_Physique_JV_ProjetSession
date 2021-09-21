#include <iostream>
#include <string>
#ifndef DEF_GAME
#define DEF_GAME


class GameBase {

private :
	std::string name;
	std::string description;

public :
	GameBase();
	GameBase(std::string nameGame, std::string descriptionGame);
	std::string getName();
	std::string getDescription();
	void launch();
	void destroy();
	void display();
	void updateInput();
	void updatePhysic();
	void updateOutput();
};

#endif