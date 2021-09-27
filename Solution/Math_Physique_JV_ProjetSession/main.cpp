#pragma comment (lib, "Winmm.lib")

#include <iostream>
#include<GL/glut.h>
#include <string>
#include <vector>
#include "Sources/Games/GameBase.h"
#include "Sources/Games/Game1.h"


using namespace std;  
#define GLUT_WINDOW_FORMAT_ID ((GLenum) 123)

void initConsole() {
	//allow a new console
	AllocConsole();
	FILE* fDummy;
	//reopen the standard flux before using them
	freopen_s(&fDummy, "CONOUT$", "w", stdout);
	freopen_s(&fDummy, "CONOUT$", "w", stderr);
	freopen_s(&fDummy, "CONIN$", "r", stdin);
	std::cout.clear();
	std::clog.clear();
	std::cerr.clear();
	std::cin.clear();
}

int main(int argc, char* argv[]) {
	//so we can use the console
	initConsole();

	//initialization of a game's table
	vector<GameBase> games;
	Game1 game1("Phase 1", "Launching some projectiles");
	games.push_back(game1);
	

	bool gameRunning = true;

	while (gameRunning) {
		bool gameChosen = false;
		int nbGameChosen;
		while (!gameChosen) {
			for (int nbGame = 0; nbGame < games.size() ; nbGame++) {
				cout << "Game " << nbGame + 1 << " - " << games[nbGame].getName() << " : " << games[nbGame].getDescription() << endl;
			}
			cout << "Which game do you choose ? " << endl;
			cin >> nbGameChosen;
			if (nbGameChosen <= games.size() && nbGameChosen > 0) {
				gameChosen = true;
			}
		}
		//launching corresponding game
		int hasExit = games[nbGameChosen - 1].launch(argc,  argv);
		if (hasExit == 0) {
			//the user closes the game
			cout << "Do you want to quit ? Yes : 1, No : 0" << endl;
			int quit;
			cin >> quit;
			if (quit == 1) {
				gameRunning = false;
			}
		}
		//la boucle recommence si l'utilisateur veut continuer
	}
	return 0;
};