#include <iostream>
#include <string>
#include "../Physic/Particule.h"
#ifndef DEF_GAMEBASE
#define DEF_GAMEBASE


class GameBase{

protected :
	std::string name;
	std::string description;

	// Global variables  
	//cam position
	double X, Z;

	//cam position
	double beta; //camera along z axis
	double angle;

	// actual vector representing the camera's direction
	double camX, camZ;

	double ANG_SPEED;
	static GameBase* instanceGameBase ;


public :
	GameBase();
	GameBase(std::string nameGame, std::string descriptionGame);
	~GameBase();
	std::string getName();
	std::string getDescription();
	
	double updateTime();

	void drawParticule(Particule particule);
	virtual int launch(int argc, char* argv[]);

	static void arrows(int key, int xx, int yy);
	static void display();
	static void keyboard(unsigned char key, int x, int y);
	static void reshape(int width, int height);
	static void updatePhysics();

	virtual void doArrows(int key, int xx, int yy);
	virtual void doDisplay();
	virtual void doKeyboard(unsigned char key, int x, int y);
	virtual void doReshape(int width, int height);
	virtual void doUpdatePhysics();
};
	



#endif