#include <iostream>
#include <string>
#include <vector>
#include "Sources/Games/GameBase.h"
#include "Sources/Games/Game1.h"

using namespace std;  



int main() {

	vector<GameBase> games;
	Game1 game1("Phase 1", "Launching some projectiles");
	games.push_back(game1);

	bool gameRunning = true;

	while (gameRunning) {
		bool gameChosen = false;
		while (!gameChosen) {
			for (int nbGame = 0; nbGame < games.size() ; nbGame++) {
				cout << "Game " << nbGame + 1 << " - " << games[nbGame].getName() << " : " << games[nbGame].getDescription() << endl;
			}
			cout << "Which game do you choose ? " << endl;
			int nbGameChosen;
			cin >> nbGameChosen;
			if (nbGameChosen <= games.size() && nbGameChosen > 0) {
				gameChosen = true;
			}
		}
		//on lance le jeu qui correspond avec un switch
		//l'utilisateur ferme le jeu
		cout << "Do you want to quit ? Yes : 1, No : 0" << endl;
		int quit;
		cin >> quit;
		if (quit == 1) {
			gameRunning = false;
		}
		//la boucle recommence si l'utilisateur veut continuer
	}
	return 0;
};