#include<iostream>
#include "game.h"
using namespace std;

int main() {
	Game* game = new Game();
	if (game) {
		game->StartEngine();
		delete game;
		game = NULL;
	}
	return 0;
}