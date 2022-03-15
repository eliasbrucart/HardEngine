#include <iostream>
#include "base_game.h"

using namespace Engine;

int main() {

    BaseGame* base = new BaseGame();

    if (base) {
        base->InitEngine();
        base->StartGLEWContext();
        base->UpdateEngine();
        base->UnloadEngine();
        delete base;
        base = NULL;
    }

    return 0;
}