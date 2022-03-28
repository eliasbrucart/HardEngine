#include <iostream>
#include "base_game.h"

using namespace Engine;

int main() {

    BaseGame* base = new BaseGame();

    if (base) {
        base->StartEngine();
        delete base;
        base = NULL;
    }

    return 0;
}