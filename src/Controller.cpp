//
// Created by Keri Southwood-Smith on 1/10/20.
//

#include "Controller.h"

bool Controller::OnInit() {
    bool success = false;

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) == 0) {
        window = SDL_CreateWindow("Breakout", SDL_WINDOWPOS_CENTERED,
                                  SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH,
                                  WINDOW_HEIGHT, SDL_WINDOW_SHOWN);

        if (window != nullptr) {
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

            if (renderer != nullptr) {
                success = true;
            }
        }
    }

    return success;
}

void Controller::CleanUp() {
    if (renderer != nullptr) {
        SDL_DestroyRenderer(renderer);
    }

    if (window != nullptr) {
        SDL_DestroyWindow(window);
    }

    SDL_Quit();
}

void Controller::Loop() {
    Ball ball = Ball(window, renderer);

    for (int i = 0; i < 2000; ++i) {
        ball.Move();
        Render(ball);
    }
}

void Controller::Render(Ball ball) {
    SDL_Color background = {0x00, 0x00, 0xff, 0xFF};
    SDL_SetRenderDrawColor(renderer, background.r, background.g, background.b, background.a);
    SDL_RenderClear(renderer);

    SDL_Rect placeBall = {ball.getXPos(), ball.getYPos(), 20, 20};
    SDL_RenderCopy(renderer, ball.getTexture(), nullptr, &placeBall);
    SDL_RenderPresent(renderer);
    SDL_Delay(1000/120);
}

