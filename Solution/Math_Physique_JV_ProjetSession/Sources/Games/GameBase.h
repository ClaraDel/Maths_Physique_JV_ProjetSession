#include <iostream>
#include <string>
#include "../Physic/Particule.h"
#ifndef DEF_GAME
#define DEF_GAME


class GameBase{

protected :
	std::string name;
	std::string description;
	//template < class T, class Alloc = allocator<T> > class list;
	
	


public :
	GameBase();
	GameBase(std::string nameGame, std::string descriptionGame);
	std::string getName();
	std::string getDescription();
	
	double updateTime(double lastTime);
	void updatePhysics(Particule* particule);
	
	void drawParticule(Particule* particule);
	int launch();

};
	void display();
	void keyboard(unsigned char key, int x, int y);
	void reshape(int width, int height);



#endif