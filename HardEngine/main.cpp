#include <iostream>
#include "base_game.h"

using namespace Engine;

int main() {

    BaseGame* base = new BaseGame();

    if (base) {
        base->CreateWindow(800, 600, "HardGamesEngine");
        base->StartGLEWContext();
        base->UpdateEngine();
        base->UnloadEngine();
        delete base;
        base = NULL;
    }

    return 0;
}