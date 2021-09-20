#include <iostream>
#ifndef DEF_GAME
#define DEF_GAME

class Game {

private :
	string name;
	string description;

public :
	Game(string nameGame, string descriptionGame);
	string getName();
	string getDescription();
};

#endif