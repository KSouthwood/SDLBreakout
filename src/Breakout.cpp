//
// Created by Keri Southwood-Smith on 1/8/20.
//
#include "Breakout.h"

int main(int argc, char* argv[]) {
    Controller game;

    if (game.OnInit()) {
        game.Loop();
        SDL_Delay(2000);
    }

    game.CleanUp();
}

