#pragma once
#include <iostream>
#include <string>
#include "../Physic/Particule.h"
#ifndef DEF_PHYSICWORLD
#define DEF_PHYSICWORLD

class PhysicWorld {
private:



public:
	double updateTime();
	static void updatePhysics();


	virtual void doUpdatePhysics();

};

#endif