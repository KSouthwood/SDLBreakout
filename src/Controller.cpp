//
// Created by Keri Southwood-Smith on 10 January 2020.
//

#include "Controller.h"

Controller::Controller() : running(true) {
    std::cout << "Controller()\n";
}

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
    textureMap.AddTexture(renderer, "ball", "ball.bmp");
    Ball ball = Ball(window, textureMap.GetID("ball"));
    textureMap.AddTexture(renderer, "brick", "brick.bmp");
    Brick brick = textureMap.GetID("brick");
    brick.SetPosition(100, 100);
    SDL_Event event;

    while (running) {
        while (SDL_PollEvent(&event)) {
            EventHandler(&event);
        }

        ball.Move();
        Render(ball, brick);
    }
}

void Controller::Render(Ball &ball, Brick &brick) {
    SDL_Color background = {0x00, 0x00, 0xff, 0xFF};
    SDL_SetRenderDrawColor(renderer, background.r, background.g, background.b,
                           background.a);
    SDL_RenderClear(renderer);

    ball.Render();
    brick.Render();
    SDL_RenderPresent(renderer);
    SDL_Delay(1000 / 240);
}

void Controller::EventHandler(SDL_Event *event) {
    if (event->type == SDL_QUIT) {
        running = false;
    }
}