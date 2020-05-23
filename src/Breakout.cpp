//
// Created by Keri Southwood-Smith on 08 January 2020.
//
#include "Breakout.h"

int main(int argc, char *argv[]) {
    Controller game;

    // SDL_Init returns 0 on success, use not to invert to true
    if (!(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER))) {
        window = SDL_CreateWindow(
            "Breakout", SDL_WINDOWPOS_CENTERED, // NOLINT(hicpp-signed-bitwise)
            SDL_WINDOWPOS_CENTERED,
            WINDOW_WIDTH, // NOLINT(hicpp-signed-bitwise)
            WINDOW_HEIGHT, SDL_WINDOW_SHOWN);

        if (window != nullptr) {
            SDL_Log("SDL_CreateWindow successful.");
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

            if (renderer != nullptr) {
                SDL_Log("SDL_CreateRenderer successful.");
                game.loop(window, renderer);
                SDL_Log("Game over. Cleaning up.");
                game.cleanUp();
            }
        }
    }

    if (renderer != nullptr) {
        SDL_DestroyRenderer(renderer);
        SDL_Log("Renderer destroyed.");
    }

    if (window != nullptr) {
        SDL_DestroyWindow(window);
        SDL_Log("Window destroyed.");
    }

    SDL_Log("Goodbye.");
    SDL_Quit();
}
