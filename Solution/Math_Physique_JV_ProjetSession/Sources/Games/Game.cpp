#include <iostream>
#include <string>
#include "Game.h"

using namespace std;

Game::Game(string nameGame, string descriptionGame):name(nameGame), description(descriptionGame){}

string Game::getName() {
	return name;
}

string Game::getDescription() {
	return description;
}