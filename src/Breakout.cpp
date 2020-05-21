//
// Created by Keri Southwood-Smith on 08 January 2020.
//
#include "Breakout.h"

int main(int argc, char *argv[]) {
    Controller game;

    // SDL_Init returns 0 on success, use not to invert to true
    if (!(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER))) {
        window = SDL_CreateWindow("Breakout", SDL_WINDOWPOS_CENTERED,   // NOLINT(hicpp-signed-bitwise)
                                  SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH,     // NOLINT(hicpp-signed-bitwise)
                                  WINDOW_HEIGHT, SDL_WINDOW_SHOWN);

        if (window != nullptr) {
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

            if (renderer != nullptr) {
                game.Loop(window, renderer);
                game.CleanUp();
            }
        }
    }

    if (renderer != nullptr) {
        SDL_DestroyRenderer(renderer);
    }

    if (window != nullptr) {
        SDL_DestroyWindow(window);
    }

    SDL_Quit();
}
