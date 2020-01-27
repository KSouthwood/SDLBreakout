//
// Created by Keri Southwood-Smith on 08 January 2020.
//
#include "Breakout.h"

int main(int argc, char* argv[]) {
    Controller game;

    if (game.OnInit()) {
        game.Loop();
    }

    game.CleanUp();
}

