#pragma comment (lib, "Winmm.lib")

#include <iostream>
#include<GL/glut.h>
#include <string>
#include <vector>
#include "Sources/Games/GameBase.h"
#include "Sources/Games/Game1.h"
#include "Sources/Games/Game2.h"
#include "Sources/Games/Game3a.h"
#include "Sources/Games/Game3b.h"
#include "Sources/Games/Game4.h"


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
	
	int nbGames = 5;
	bool gameRunning = true;

	while (gameRunning) {
		bool gameChosen = false;
		int nbGameChosen;
		while (!gameChosen) {
			cout << "Game 1 (Phase 1) - Launching some projectiles" << endl;	
			cout << "Game 2 (Phase 2) - Blob" << endl;
			cout << "Game 3 (Phase 3) - Rotate rigidbody" << endl;
			cout << "Game 4 (Phase 3) - Car accident" << endl;
			cout << "Game 5 (Phase 4) - Cube collision" << endl;

			cout << "Which game do you choose ? " << endl;
			cin >> nbGameChosen;
			if (nbGameChosen <= nbGames && nbGameChosen > 0) {
				gameChosen = true;
			}
		}
		//creating and launching corresponding game
		switch (nbGameChosen) {
		case 1: {
			Game1 game1("Phase 1", "Launching some projectiles");
			game1.launch(argc, argv);
			break;
		}
		case 2: {
			Game2 game2("Phase 2", "Controlling a blob");
			game2.launch(argc, argv);
			break;
		}
		case 3: {
			Game3a game3a("Phase 3", "Rotate rigidbody");
			game3a.launch(argc, argv);
			break;
		}
		case 4: {
			Game3b game3b("Phase 3", "Car accident");
			game3b.launch(argc, argv);
			break;
		}
		case 5: {
			Game4 game4("Phase 4", "Cube collision");
			game4.launch(argc, argv);
			break;
		}
		default:

			break;
		}
		
		
		
	}
	return 0;
};