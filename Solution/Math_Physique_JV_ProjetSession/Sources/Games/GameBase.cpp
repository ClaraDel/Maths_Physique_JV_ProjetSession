#include <iostream>
#include <string>
#include "GameBase.h"

using namespace std;

GameBase::GameBase(){}
GameBase::GameBase(string nameGame, string descriptionGame):name(nameGame), description(descriptionGame){}

string GameBase::getName() {
	return name;
}

string GameBase::getDescription() {
	return description;
}