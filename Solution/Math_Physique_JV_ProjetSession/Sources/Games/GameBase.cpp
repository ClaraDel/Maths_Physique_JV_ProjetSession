#include <iostream>
#include <windows.h>
#include<GL/glut.h>
#include <string>
#include "GameBase.h"
#include <ctime>
#include "../Physic/Particule.h"

using namespace std;



GameBase::GameBase(){
	name = "GameBase";
	description = "Common game base with all games";
}

GameBase::GameBase(string nameGame, string descriptionGame){
	name = nameGame;
	description = descriptionGame;
}

GameBase::~GameBase() {
	instanceGameBase = nullptr;
}

string GameBase::getName() {
	return name;
}

string GameBase::getDescription() {
	return description;
}

void GameBase::drawParticule(Particule particule) { 
}

double GameBase::updateTime() {
	static double current_time = 0;
	static double last_time = 0;

	last_time = current_time;
	current_time = glutGet(GLUT_ELAPSED_TIME);
	//calculates the time spent between two frames 
	double deltaTime = (current_time - last_time) * 0.001; 
	return deltaTime;
}




void GameBase::doUpdatePhysics() {
}


void GameBase::updatePhysics() {
	instanceGameBase -> doUpdatePhysics();
}



void bouclePrincipale() {
	//on appelle update time (gui)
	// double deltatime = Xms
	//on appelle la physic via physic wolrd updatephysic(time)
	// tableauparticule = pW.updatePhysic(deltaTime, tableauparticule)
	//on appelle le gui pour mettre à jour via le display -> draw particule
	// gui.display(tableaparticule)
}

