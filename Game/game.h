#ifndef GAME_H
#define GAME_H

#include "base_game.h"

using namespace Engine;

class Game: public BaseGame {
private:
public:
	Game();
	~Game();
	void InitGame() override;
	void UpdateGame() override;
	void UnloadGame() override;
};

#endif