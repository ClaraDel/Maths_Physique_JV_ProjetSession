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
	double X;
	double Z;
	//cam direction
	double beta; //camera along z axis
	double angle;
	// actual vector representing the camera's direction
	double camX;
	double camZ;
	double ANG_SPEED;
	static GameBase* instanceGameBase ;


public :
	GameBase();
	GameBase(std::string nameGame, std::string descriptionGame);
	~GameBase();
	std::string getName();
	std::string getDescription();
	
	double updateTime(double lastTime);
	void updatePhysics(Particule* particule);
	
	void drawParticule(Particule* particule);
	virtual int launch(int argc, char* argv[]);

	static void arrows(int key, int xx, int yy);
	static void display();
	static void keyboard(unsigned char key, int x, int y);
	static void reshape(int width, int height);

	virtual void arrows2(int key, int xx, int yy);
	virtual void display2();
	virtual void keyboard2(unsigned char key, int x, int y);
	virtual void reshape2(int width, int height);
};
	



#endif